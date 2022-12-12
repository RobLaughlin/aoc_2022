#include "TimedInstruction.h"

TimedInstruction::TimedInstruction() 
    : timing(0), quantity(0) {};

TimedInstruction::TimedInstruction(int timing, int quantity) 
    : timing(timing), quantity(quantity) {};
