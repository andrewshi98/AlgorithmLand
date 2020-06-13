#include <iostream>
#include <vector>
#include <stack>
#include "BFKengine.hpp"
#include "BFKparser.hpp"

namespace parse {

    std::vector<script::Command*> *parse(std::ifstream &is) {
        std::vector<script::Command*> *cmdList = new std::vector<script::Command *>;
        std::stack<script::LoopStart*> loopStack;
        char parseChar;

        while (!is.eof()) {
            is.get(parseChar);
            script::Command *newCmd = 0;
            script::LoopStart *loop = new script::LoopStart(cmdList->size(), 0);
            script::LoopStart *loopStart;
            switch (parseChar) {
                case '>':
                newCmd = new script::DataOp(cmdList->size(), script::IncP);
                break;
                case '<':
                newCmd = new script::DataOp(cmdList->size(), script::DecP);
                break;
                case '+':
                newCmd = new script::DataOp(cmdList->size(), script::IncD);
                break;
                case '-':
                newCmd = new script::DataOp(cmdList->size(), script::DecD);
                break;
                case '.':
                newCmd = new script::DataOp(cmdList->size(), script::OutD);
                break;
                case ',':
                newCmd = new script::DataOp(cmdList->size(), script::AccD);
                break;
                case '[':
                loopStack.push(loop);
                newCmd = loop;
                break;
                case ']':
                if (loopStack.size() == 0) {
                    std::cout << "Extra ] detected in code. Position: " << cmdList->size() << std::endl;
                    throw 1;
                } else {
                    loopStart =  loopStack.top();
                    loopStack.pop();
                    int loopStartLoc = loopStart->cmdPos;
                    loopStart->loopEnd = cmdList->size();
                    newCmd = new script::LoopEnd(cmdList->size(), loopStartLoc);
                }
                break;
            }
            if (newCmd != 0) {
                cmdList->push_back(newCmd);
            }
        }
        if (loopStack.size() != 0) {
            std::cout << "Unclosed loop in code. Position: " << loopStack.top()->cmdPos << std::endl;
            throw 2;  
        }
        return cmdList;
    }
}
