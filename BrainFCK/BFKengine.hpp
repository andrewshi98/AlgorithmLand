#pragma once

#include <string>
#include <iostream>
#include <vector>

namespace script {

    class Environment {
    public:
        Environment();
        ~Environment();
        char *curPointer();
        void incPointer();
        void decPointer();
        std::ostream& operator << (char &os);
        std::istream& operator >> (char &is);
    private:
        long memSize;
        void *envMem;
        char *dataPtr;
    };

    class Command {
    public:
        virtual int execute(Environment &e) = 0;
        int cmdPos;
    };

    enum DataOpType {
        IncP, DecP, IncD, DecD, OutD, AccD
    };

    class DataOp : public Command {
    public:
        DataOp(int cmdPos, DataOpType type);
        DataOpType type;
        int cmdPos;
        int execute(Environment &e);
    };

    class LoopStart : public Command {
    public:
        LoopStart();
        LoopStart(int cmdPos, int loopEnd);
        int loopEnd;
        int cmdPos;
        int execute(Environment &e);
    };

    class LoopEnd : public Command {
    public:
        LoopEnd();
        LoopEnd(int cmdPos, int loopStart);
        int loopStart;
        int cmdPos;
        int execute(Environment &e);
    };

}