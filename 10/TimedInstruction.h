#pragma once

class TimedInstruction {
public:
    TimedInstruction();
    TimedInstruction(int timing, int quantity);
    int timing;
    int quantity;
};