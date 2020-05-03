//
// Created by LENOVO on 01/05/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_TABULIST_H
#define UNBOUNDEDKNAPSACKPROBLEM_TABULIST_H

#include "commun.h"
#include <set>

class TabuList {
public:
    virtual bool push(Solution solution) = 0;
    virtual Solution pop() = 0;
    virtual bool contains(Solution solution) = 0;
    virtual size_t size() = 0;
};


class TabuListBestValueSet : public TabuList{
public:
    TabuListBestValueSet(const std::set<Solution, std::greater<>> &set);

    bool push(Solution solution) override;

    Solution pop() override;

    bool contains(Solution solution) override;

    size_t size() override;

private:
    std::set<Solution, std::greater<>> set;
};



#endif //UNBOUNDEDKNAPSACKPROBLEM_TABULIST_H
