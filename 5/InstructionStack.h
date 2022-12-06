#pragma once
#include <vector>
#include <stack>
#include <array>
#include <exception>
#include <sstream>
#include <string>

struct Instruction {
    int num;
    int from;
    int to;
};

class InstructionStack {
public:
    typedef std::stack<char> Charstack;
    InstructionStack();
    InstructionStack(std::vector<Charstack> stacks, std::vector<Instruction> instructions);
    void run(bool moveAllAtOnce);
    std::string top();
private:
    std::vector<Charstack> stacks;
    std::vector<Instruction> instructions;
};