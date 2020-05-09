//
// Created by LENOVO on 08/05/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_ADDONELOCALIZER_H
#define UNBOUNDEDKNAPSACKPROBLEM_ADDONELOCALIZER_H

#include "Localizer.h"
#include <unordered_set>


class AddOneLocalizer : public Localizer{
public:
    Neighbourhood getNeighbors(Solution center) override;

    AddOneLocalizer(const Instance &instance);

private:
    int sumWeight(Solution const& solution);
    //int selectObject(std::unordered_set<Object> excluded);
};


#endif //UNBOUNDEDKNAPSACKPROBLEM_ADDONELOCALIZER_H
