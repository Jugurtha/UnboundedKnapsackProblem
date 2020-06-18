//
// Created by LENOVO on 01/05/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_COMMUN_H
#define UNBOUNDEDKNAPSACKPROBLEM_COMMUN_H

#include <vector>
#include <tuple>
#include <map>
#include <algorithm>
#include <iostream>


struct Object{
    unsigned int weight;
    int value;
};

using Objects =   std::vector<Object>;


struct Instance
{
    unsigned int  maxWeight;
    Objects objects;
};

struct Result
{
    int value;
    long weight;
    double executionTime;
};

struct Solution
{
    /*
    Solution(const std::vector<int> &tuple, int value) : tuple(tuple), value(value) {}
    Solution(Instance const& instance) : tuple(instance.objects.size(), 0), value(0) {}
    Solution(unsigned int nbrObjects) : tuple(nbrObjects, 0), value(0) {}
    */

    std::vector<int> tuple;
    int value;

    bool operator<(const Solution &rhs) const {
        return value < rhs.value;
    }

    bool operator>(const Solution &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Solution &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Solution &rhs) const {
        return !(*this < rhs);
    }

    bool operator==(const Solution &rhs) const {
        return value == rhs.value;
    }

    bool operator!=(const Solution &rhs) const {
        return !(rhs == *this);
    }
};


enum TabuType {ADD_ONE, SWITCH_OBJ, NBR_TYPES};
const std::string TABU_TYPE_STRING[] = {std::string("ADD_ONE"), std::string("SWITCH_OBJ"), std::string("NBR_TYPES")};

#endif //UNBOUNDEDKNAPSACKPROBLEM_COMMUN_H
