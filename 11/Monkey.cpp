#include "Monkey.h"

Monkey::Monkey() 
    :   items(std::deque<long long>()),
        operation([](long long& item) {}),
        test([](const long long& item) {return 0;})
{};

Monkey::Monkey(std::vector<long long> items, std::function<void (long long& item)> operation, std::function<int (const long long& item)> test) 
    :   items(std::deque<long long>()),
        operation(operation),
        test(test)
{
    for (int item : items) {
        this->items.push_back(item);
    }
};

std::ostream& operator<<(std::ostream& os, Monkey& monkey) {
    for (int i = 0; i < monkey.items.size(); i++) {
        long long item = monkey.items.front();
        os << item << " ";

        monkey.items.pop_front();
        monkey.items.push_back(item);
    }

    return os;
}