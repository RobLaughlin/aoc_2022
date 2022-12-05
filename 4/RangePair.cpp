#include "RangePair.h"

bool RangePair::hasContainment() {
    const Range r1 = this->r1;
    const Range r2 = this->r2;

    bool r1inr2 = (r1.min >= r2.min && r1.max <= r2.max);
    bool r2inr1 = (r2.min >= r1.min && r2.max <= r1.max);
    return (r1inr2 || r2inr1);
}

bool RangePair::hasOverlap() {
    const Range r1 = this->r1;
    const Range r2 = this->r2;

    return (std::min(r1.max, r2.max) >= std::max(r1.min, r2.min));
}

std::ostream& operator<<(std::ostream& os, const RangePair& rp)
{
    os << '[' << rp.r1.min << ", " << rp.r1.max << "] ";
    os << '[' << rp.r2.min << ", " << rp.r2.max << "] ";
    return os;
}

