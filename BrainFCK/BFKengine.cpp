#include "BFKengine.hpp"

#define ENV_INIT_SIZE 64

namespace script {
    Environment::Environment() {
        memSize = ENV_INIT_SIZE;
        envMem = new char[ENV_INIT_SIZE];
        dataPtr = (char *)envMem;
    }

    Environment::~Environment() {
        delete (char *)envMem;
    }

    char *Environment::curPointer() {
        return dataPtr;
    }

    void Environment::incPointer() {
        // TODO: memregion expansion
        dataPtr += 1;
    }

    void Environment::decPointer() {
        // Check boundary
        if (dataPtr > envMem) {
            dataPtr -= 1;
        }
    }

    std::ostream& Environment::operator<<(char &os) {
        return (std::cout << os);
    }

    std::istream& Environment::operator>>(char &is) {
        return (std::cin.get(is));
    }

    DataOp::DataOp(int cmdPos, DataOpType type): cmdPos(cmdPos), type(type) {}

    int DataOp::execute(Environment &e) {
        switch (type) {
            case IncP:
                e.incPointer();
                break;
            case DecP:
                e.decPointer();
                break;
            case IncD:
                *e.curPointer() += 1;
                break;
            case DecD:
                *e.curPointer() -= 1;
                break;
            case OutD:
                e << *e.curPointer();
                break;
            case AccD:
                e >> *e.curPointer();
                break;
        }
        return cmdPos + 1;
    }

    LoopStart::LoopStart() {}
    LoopStart::LoopStart(int cmdPos, int loopEnd): cmdPos(cmdPos), loopEnd(loopEnd) {}

    int LoopStart::execute(Environment &e) {
        if (*e.curPointer() != 0) {
            return cmdPos + 1;
        } else {
            return loopEnd + 1;
        }
    }

    LoopEnd::LoopEnd() {}
    LoopEnd::LoopEnd(int cmdPos, int loopStart): cmdPos(cmdPos), loopStart(loopStart) {}

    int LoopEnd::execute(Environment &e) {
        return loopStart;
    }
}