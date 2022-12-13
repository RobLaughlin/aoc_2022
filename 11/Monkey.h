#pragma once
#include <deque>
#include <vector>
#include <functional>
#include <iostream>

class Monkey {
public:
    Monkey();
    Monkey(std::vector<long long> items, std::function<void (long long& item)> operation, std::function<int (const long long& item)> test);
    std::deque<long long> items;

    // Operation function on items
    std::function<void (long long& item)> operation;

    // Return which monkey to throw to
    std::function<int (const long long& item)> test;

    friend std::ostream& operator<<(std::ostream& os, Monkey& monkey);
private:
};