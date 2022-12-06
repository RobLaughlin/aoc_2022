#include "InstructionStack.h"

InstructionStack::InstructionStack() {
    this->stacks = std::vector<Charstack>();
    this->instructions = std::vector<Instruction>();
}

InstructionStack::InstructionStack(std::vector<Charstack> stacks, std::vector<Instruction> instructions) {
    this->stacks = stacks;
    this->instructions = instructions;
}

void InstructionStack::run(bool moveAllAtOnce) {
    for (Instruction instruction : this->instructions) {
        const int num = instruction.num;
        const int from = instruction.from;
        const int to = instruction.to;

        // Check if from and to are valid indices and num is valid
        if (from < 0 || from > this->stacks.size() || this->stacks[from].size() < num || 
            to < 0 || to > this->stacks.size())
        {
            std::stringstream ss;
            ss << "There was an error moving " << num << " blocks from index " << from << " to index " << to << ".";
            throw std::runtime_error(ss.str());
        }


        if (moveAllAtOnce) {
            Charstack buffer = Charstack();
            for (int i = 0; i < num; i++){
                buffer.push(this->stacks[from].top());
                this->stacks[from].pop();
            }

            for (int i = 0; i < num; i++){
                this->stacks[to].push(buffer.top());
                buffer.pop();
            }
        }
        else {
            for (int i = 0; i < num; i++){
                this->stacks[to].push(this->stacks[from].top());
                this->stacks[from].pop();
            }
        }
    }
}

std::string InstructionStack::top() {
    std::stringstream ss;
    for (Charstack stack : this->stacks) {
        ss << stack.top();
    }
    return ss.str();
}