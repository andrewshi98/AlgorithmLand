#include <iostream>
#include <fstream>
#include <vector>
#include "BFKparser.hpp" 
#include "BFKengine.hpp"

using namespace script;
using namespace std;

int main(int argc, char *argv[]) {
    Environment e;
    ifstream myfile;
    myfile.open ("example.txt");

    vector<Command*> *cmdList = parse::parse(myfile);

    myfile.close();
    
    int cmdPtr = 0;
    while (cmdPtr != cmdList->size()) {
        Command *cmd = cmdList->at(cmdPtr);
        cmdPtr = cmd->execute(e);
    }

    return 0;
}