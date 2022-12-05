#pragma once
#include <iostream>
#include "Range.h"

struct RangePair {
    Range r1;
    Range r2;
    bool hasContainment();
    bool hasOverlap();
    friend std::ostream& operator<<(std::ostream& os, const RangePair& rp);
};