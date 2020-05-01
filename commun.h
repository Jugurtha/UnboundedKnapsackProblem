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
    int weight;
    int value;
};

using Objects =   std::vector<Object>;

struct Solution
{
    std::vector<int> tuple;
    int value;
};

#endif //UNBOUNDEDKNAPSACKPROBLEM_COMMUN_H
