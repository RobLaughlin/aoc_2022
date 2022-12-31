#pragma once
#include "BinaryNode.hpp"
#include "HashableTuple.hpp"
#include <unordered_map>
#include <string>


namespace Solution21 {
    class Solution {
    public:
        typedef std::unique_ptr<BinaryNode<int>> NodePtr;
        typedef HTuple<std::string, char, std::string> NodeState;
        typedef std::unordered_map<NodeState, long long> StateMap;
        typedef std::shared_ptr<StateMap> Memo;

        static const std::string INPUT_FILENAME;

        Solution();
        long long root_yell() const;
        long long find_human_number() const;
    private:
        NodePtr root;
        static const std::unordered_map<char, char> INVERSE_OPERATOR;

        long long calc(const NodePtr& node, bool inverse, Memo memo=std::make_shared<StateMap>()) const;
    };
};