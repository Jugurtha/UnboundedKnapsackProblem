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

#endif //UNBOUNDEDKNAPSACKPROBLEM_COMMUN_H
