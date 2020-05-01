//
// Created by LENOVO on 01/05/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_LOCALIZER_H
#define UNBOUNDEDKNAPSACKPROBLEM_LOCALIZER_H

#include "commun.h"
#include "Neighbourhood.h"

class Localizer {
public:
    Neighbourhood virtual getNeighbors(Solution center) = 0;
};


#endif //UNBOUNDEDKNAPSACKPROBLEM_LOCALIZER_H
