#include <regex>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

static const string INPUT_FILENAME = "input.txt";
static const regex MATCH_DIGIT("-?\\d+");

struct Range {
    int min;
    int max;
};

struct RangePair {
    Range r1;
    Range r2;
    friend ostream& operator<<(ostream& os, const RangePair& rp);
};

ostream& operator<<(ostream& os, const RangePair& rp)
{
    os << '[' << rp.r1.min << ", " << rp.r1.max << "] ";
    os << '[' << rp.r2.min << ", " << rp.r2.max << "] ";
    return os;
}

vector<RangePair> preprocess(const string& input_file) {
    vector<RangePair> pairs = vector<RangePair>();

    ifstream input;
    input.open(input_file);
    if (!input.is_open()) {
        throw invalid_argument("Error reading input file " + input_file);
    }

    string line;
    while (getline(input, line)) {
        smatch match;
        Range r1;
        Range r2;

        regex_search(line, match, MATCH_DIGIT);
        r1.min = stoi(match.str());
        line = match.suffix().str();
        
        regex_search(line, match, MATCH_DIGIT);
        r1.max = -stoi(match.str());
        line = match.suffix().str();

        regex_search(line, match, MATCH_DIGIT);
        r2.min = stoi(match.str());
        line = match.suffix().str();

        regex_search(line, match, MATCH_DIGIT);
        r2.max = -stoi(match.str());
        line = match.suffix().str();

        RangePair p ={r1, r2};
        pairs.push_back(p);
    }

    return pairs;
}

bool hasContainment(const RangePair& pair) {
    const Range r1 = pair.r1;
    const Range r2 = pair.r2;

    bool r1inr2 = (r1.min >= r2.min && r1.max <= r2.max);
    bool r2inr1 = (r2.min >= r1.min && r2.max <= r1.max);
    return (r1inr2 || r2inr1);
}

bool hasOverlap(const RangePair& pair) {
    const Range r1 = pair.r1;
    const Range r2 = pair.r2;

    return (min(r1.max, r2.max) >= max(r1.min, r2.min));
}

int main() {
    int containments = 0;
    int overlaps = 0;

    vector<RangePair> pairs = preprocess(INPUT_FILENAME);
    for (RangePair pair : pairs) {
        if (hasContainment(pair)) { containments++; }
    }

    for (RangePair pair : pairs) {
        if (hasOverlap(pair)) { overlaps++; }
    }

    cout << containments << endl;
    cout << overlaps << endl;
    return 0;
}