//
// Created by CHAKER Jugurtha on 25/04/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_BRANCHANDBOUND_H
#define UNBOUNDEDKNAPSACKPROBLEM_BRANCHANDBOUND_H

#include <vector>
#include <tuple>
#include <map>
#include <algorithm>
#include <iostream>

struct Object{
    int weight;
    int value;
};

struct Evaluation{
            bool isAsolution;
            int value;
            std::vector<int> tuple;
};

struct Solution
{
        std::vector<int> tuple;
        int value;
};

struct Node
{
    int depth;
    std::vector<int> tuple;
    int eval;
};

using Objects =   std::vector<Object>;

class BranchAndBound {
public:
    BranchAndBound(unsigned int maxWeight, Objects objects);
    Solution search();
private:
    unsigned int maxWeight;
    std::vector<int> weights;
    std::vector<int> values;

    std::vector<int> separate(unsigned int maxWeight, Objects sortedObjects, std::vector<int> tuple);
    bool isASolution(unsigned int maxWeight, Objects sortedObjects,  std::vector<int> tuple);
    Evaluation evaluate(unsigned int maxWeight, Objects sortedObjects, std::vector<int> tuple);
    Objects sortObjects();
    Solution findSolution(unsigned int maxWeight, Objects sortedObjects);
};

#endif //UNBOUNDEDKNAPSACKPROBLEM_BRANCHANDBOUND_H
