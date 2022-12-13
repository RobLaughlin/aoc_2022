#include "Solution.h"
#include <fstream>
#include <regex>
#include <unordered_map>
#include <math.h>

const std::string Solution::INPUT_FILENAME = "input.txt";

Solution::Solution() 
    : monkeys(std::vector<Monkey>())
{
    std::ifstream input(INPUT_FILENAME);
    
    std::string line;   
    std::vector<long long> items;
    std::function<void (long long& item)> operation;
    std::function<int (const long long& item)> test;

    // Need this to keep the stress number managable
    long long product = 1;

    while (std::getline(input, line)) {
        if (line[0] == 'M') {
            // Hit the monkey label
            continue;
        }
        else if (line[2] == 'S') {
            // Starting items label
            std::smatch match;
            const std::regex digits("\\d+");

            while (std::regex_search (line, match, digits)) {
                items.push_back(std::stoi(match.str()));
                line = match.suffix().str();
            }
        }
        else if (line[2] == 'O') {
            // Operation label
            const char op = line[23];

            const std::string operend = line.substr(25);

            operation = [op, operend](long long& item) {
                bool old = operend == "old";
                switch (op) {
                    case '+': item += old ? item : std::stoi(operend); return;
                    case '*': item *= old ? item : std::stoi(operend); return;
                    default: return;
                }
            };
        }
        else if (line[2] == 'T') {
            // Test label
            const long long divisor = std::stoi(line.substr(21));
            product *= divisor;

            std::getline(input, line);
            const long long true_monkey = std::stoi(line.substr(29));

            std::getline(input, line);
            const long long false_monkey = std::stoi(line.substr(30));

            test = [divisor, true_monkey, false_monkey](const long long& item) {
                return (item % divisor == 0) ? true_monkey : false_monkey;
            };

            // Add the constructed monkey to the list.
            monkeys.push_back(Monkey(items, operation, test));
            items = std::vector<long long>();
        }
    }

    this->divisibility_product = product;
    input.close();
}

long long Solution::monkey_business(int rounds, bool manage_stress) const {
    std::unordered_map<int, long long> inspections;
    std::vector<Monkey> monkeys = this->monkeys;

    for (int r = 0; r < rounds; r++) {
        for (int m = 0; m < monkeys.size(); m++) {
            Monkey& monkey = monkeys.at(m);

            if (inspections.find(m) == inspections.end()) {
                inspections[m] = 0;
            }

            while (!monkey.items.empty()) {
                // Inspection
                inspections[m]++;

                long long item = monkey.items.front();
                monkey.operation(item);

                if (manage_stress) {
                    item = floor(item / 3);
                } else {
                    // Divide by the product of divsiibility checks to keep the stress managable
                    item = item % this->divisibility_product;
                }
                
                int idx_to = monkey.test(item);
                monkeys[idx_to].items.push_back(item);
                monkey.items.pop_front();
            }
        }
    }
    
    // Largest in [0] and second to largest in [1]
    long long max_inspections[2] = {0, 0};
    for (auto const& [_, inspection] : inspections) {
        if (inspection > max_inspections[0]) {
            max_inspections[1] = max_inspections[0];
            max_inspections[0] = inspection;
        }
        else if (inspection > max_inspections[1]) {
            max_inspections[1] = inspection;
        }
    }

    // Return "monkey business"
    return max_inspections[0] * max_inspections[1];
}