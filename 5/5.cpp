#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <string>
#include <regex>
#include <array>

using namespace std;

struct ParsedInput {
    vector<stack<char>> stacks;
    vector<array<int, 3>> instructions;
};

ParsedInput preprocess() {
    vector<stack<char>> stacks = vector<stack<char>>();

    ifstream input;
    input.open("input.txt");

    string line;
    while(getline(input, line)) {
        if (line[1] == '1') { break; }
        if (stacks.size() == 0) {
            const int width = (line.size()+1) / 4;
            for (int i = 0; i < width; i++) {
                stacks.push_back(stack<char>());
            }
        }

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
        stack<char>& stack = stacks[s];
        vector<char> buffer = vector<char>();

        while (!stack.empty()) {
            char c = stack.top();
            buffer.push_back(c);
            stack.pop();
        }

        for (int i = 0; i < buffer.size(); i++) {
            stack.push(buffer[i]);
        } 
    }

    getline(input, line);

    vector<array<int, 3>> instructions = vector<array<int, 3>>();
    while (getline(input, line)) {
        smatch match;
        array<int, 3> instruction {0,0,0};

        for (int i = 0; i < instruction.size(); i++) {
            regex_search(line, match, regex("\\d+"));
            instruction[i] = stoi(match.str());
            line = match.suffix().str();
        }

        instructions.push_back(instruction);
    }


    return ParsedInput {stacks, instructions};
}

int main() {
    ParsedInput data = preprocess();

    // Part 1
    // for (array<int, 3> instruction : data.instructions) {
    //     int quantity = instruction[0];
    //     int from = instruction[1]-1;
    //     int to = instruction[2]-1;

    //     for (int i = 0; i < quantity; i++){
    //         data.stacks[to].push(data.stacks[from].top());
    //         data.stacks[from].pop();
    //     }
    // }

    // Part 2
    for (array<int, 3> instruction : data.instructions) {
        int quantity = instruction[0];
        int from = instruction[1]-1;
        int to = instruction[2]-1;

        stack<char> buffer = stack<char>();

        for (int i = 0; i < quantity; i++){
            buffer.push(data.stacks[from].top());
            data.stacks[from].pop();
        }

        for (int i = 0; i < quantity; i++){
            data.stacks[to].push(buffer.top());
            buffer.pop();
        }
    }

    for (stack<char> s : data.stacks) {
        cout << s.top();
    }
    cout << endl;
    return 0;
}