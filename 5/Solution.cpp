#include "Solution.h"

Solution::Solution(const std::string& input_file) {
    std::vector<std::stack<char>> stacks = std::vector<std::stack<char>>();

    std::ifstream input;
    input.open(input_file);

    if (!input.is_open()) {
        throw std::invalid_argument("Error reading input file");
    }

    std::string line;
    while(std::getline(input, line)) {
        // If we hit a digit we're done parsing blocks
        if (line[1] == '1') { break; }

        // Initialization step, we need to figure out how big to make our vector of stacks
        if (stacks.size() == 0) {
            const int width = (line.size()+1) / 4;
            for (int i = 0; i < width; i++) {
                stacks.push_back(std::stack<char>());
            }
        }

        // Actually populating the stacks
        for (int i = 1; i < line.length(); i += 4) {
            char c = line[i];
            if (c != ' ') {
                const int idx = (i - 1) / 4;
                stacks[idx].push(c);
            }
        }
    }

    // Reverse the stacks
    for (int s = 0; s < stacks.size(); s++) {
        std::stack<char>& stack = stacks[s];
        std::vector<char> buffer = std::vector<char>();

        while (!stack.empty()) {
            char c = stack.top();
            buffer.push_back(c);
            stack.pop();
        }

        for (int i = 0; i < buffer.size(); i++) {
            stack.push(buffer[i]);
        } 
    }

    // Read the blank line
    getline(input, line);

    // Now that we've parsed all the blocks, we need to parse the instructions
    std::vector<Instruction> instructions = std::vector<Instruction>();
    while (getline(input, line)) {
        std::smatch match;
        int instruction[3] = {0,0,0};

        for (int i = 0; i < 3; i++) {
            std::regex_search(line, match, std::regex("\\d+"));
            instruction[i] = stoi(match.str());
            line = match.suffix().str();
        }

        // Instructions are indexed starting 1 so we subtract 1 to index starting at 0
        Instruction ins {instruction[0], instruction[1]-1, instruction[2]-1};
        instructions.push_back(ins);
    }

    this->start_stack = InstructionStack(stacks, instructions);
    this->instruction_stack = InstructionStack(stacks, instructions);
}

std::string Solution::one_at_a_time() {
    this->instruction_stack.run(false);
    std::string output = this->instruction_stack.top();

    this->instruction_stack = this->start_stack;
    return output;
}

std::string Solution::some_at_a_time() {
    this->instruction_stack.run(true);
    std::string output = this->instruction_stack.top();

    this->instruction_stack = this->start_stack;
    return output;
}