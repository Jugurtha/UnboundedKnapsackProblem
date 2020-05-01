//
// Created by CHAKER Jugurtha on 25/04/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_BRANCHANDBOUND_H
#define UNBOUNDEDKNAPSACKPROBLEM_BRANCHANDBOUND_H


#include "commun.h"



class BranchAndBound {
public:
    BranchAndBound(unsigned int maxWeight, Objects const& objects);
    Solution search();
    struct Evaluation{
        bool isAsolution;
        double value;
        std::vector<int> tuple;
    };


    struct Node
    {
        int depth;
        std::vector<int> tuple;
        double eval;
    };
private:
    unsigned int maxWeight;
    std::vector<int> weights;
    std::vector<int> values;

    std::vector<int> separate(unsigned int maxWeight, Objects const& sortedObjects, std::vector<int> tuple);
    bool isASolution(unsigned int maxWeight, Objects const& sortedObjects,  std::vector<int> tuple);
    Evaluation evaluate(unsigned int maxWeight, Objects const& sortedObjects, std::vector<int> tuple);
    Objects sortObjects();
    Solution findSolution(unsigned int maxWeight, Objects const& sortedObjects);
};

#endif //UNBOUNDEDKNAPSACKPROBLEM_BRANCHANDBOUND_H
