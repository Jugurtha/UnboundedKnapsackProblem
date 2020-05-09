//
// Created by LENOVO on 01/05/2020.
//

#include "TabuList.h"

TabuListBestValueSet::TabuListBestValueSet(const std::set<Solution, std::less<>> &set) : set(set) {}

bool TabuListBestValueSet::push(Solution solution) {
    set.insert(solution);
    return true;
}

Solution TabuListBestValueSet::pop() {
    if(!set.empty())
    {
        auto copy(*set.cbegin());
        set.erase(set.cbegin());
        return copy;
    }
    return Solution{};
}

bool TabuListBestValueSet::contains(Solution solution) {
    return set.count(solution)>0;
}

size_t TabuListBestValueSet::size() {
    return set.size();
}

TabuListBestValueSet::TabuListBestValueSet() {}
