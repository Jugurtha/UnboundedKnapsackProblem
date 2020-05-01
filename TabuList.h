//
// Created by LENOVO on 01/05/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_TABULIST_H
#define UNBOUNDEDKNAPSACKPROBLEM_TABULIST_H

#include "commun.h"

class TabuList {
public:
    bool virtual push(Solution solution) = 0;
    Solution virtual pop() = 0;
    bool virtual contains(Solution solution) = 0;
    size_t virtual size() = 0;
};





#endif //UNBOUNDEDKNAPSACKPROBLEM_TABULIST_H
