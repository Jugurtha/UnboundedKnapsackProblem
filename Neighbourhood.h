//
// Created by LENOVO on 01/05/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_NEIGHBOURHOOD_H
#define UNBOUNDEDKNAPSACKPROBLEM_NEIGHBOURHOOD_H

#include "commun.h"
#include <set>

class Neighbourhood {
public:
    Neighbourhood(const std::set<Solution> &set) : set(set) {}
    auto begin(){ return set.begin();};
    auto end(){ return set.end();}
    auto cbegin(){ return set.cbegin();};
    auto cend(){ return set.cend();}
    Solution first() {*(set.begin());}
private:
    std::set<Solution> set;
};


#endif //UNBOUNDEDKNAPSACKPROBLEM_NEIGHBOURHOOD_H
