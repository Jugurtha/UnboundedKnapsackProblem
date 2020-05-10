//
// Created by LENOVO on 08/05/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_ADDONELOCALIZER_H
#define UNBOUNDEDKNAPSACKPROBLEM_ADDONELOCALIZER_H

#include "Localizer.h"
#include <unordered_set>


class AddOneLocalizer : public Localizer{
public:
    Neighbourhood getNeighbors(Solution const& center) override;

    AddOneLocalizer(const Instance &instance);
};


#endif //UNBOUNDEDKNAPSACKPROBLEM_ADDONELOCALIZER_H
