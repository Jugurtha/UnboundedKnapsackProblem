//
// Created by LENOVO on 09/05/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_SWITCHOBJECTSLOCALIZER_H
#define UNBOUNDEDKNAPSACKPROBLEM_SWITCHOBJECTSLOCALIZER_H

#include <random>
#include <chrono>
#include "Localizer.h"


class SwitchObjectsLocalizer : public  Localizer{
public:
    SwitchObjectsLocalizer(const Instance &instance, const unsigned int nbrTries);
    Neighbourhood getNeighbors(Solution const& center) override;

private:
    const unsigned int nbrTries;
    const unsigned int nbrObjects;
    const std::vector<double> ratios;
    std::random_device dev;
    std::mt19937 rng;
    //std::exponential_distribution<> dist;
    std::discrete_distribution<> dist;

    std::vector<double> getRatios();

};


#endif //UNBOUNDEDKNAPSACKPROBLEM_SWITCHOBJECTSLOCALIZER_H
