//
// Created by LENOVO on 09/05/2020.
//

#include "SwitchObjectsLocalizer.h"
#include <map>
#include <iomanip>

Neighbourhood SwitchObjectsLocalizer::getNeighbors(Solution const& center) {
    Neighbourhood neighbourhood;
    Solution next(center);
    unsigned int iteration = 0;

    while(iteration < nbrTries)
    {
        unsigned int i = static_cast <int> (std::floor(dist(rng))) % nbrObjects;//std::cout << "i : " << i;
        unsigned int j = static_cast <int> (std::floor(dist(rng))) % nbrObjects;//std::cout << ", j : " << j << '\n';

        if(next.tuple[i]==0)
        {
            iteration++;
            continue;
        }

        next.tuple[i]--;
        next.tuple[j]++;

        if(sumWeight(next)<=maxWeight)
        {
            next.value -= sortedObjects[i].value;
            next.value += sortedObjects[j].value;
            break;
        }
        else
        {
            next.tuple[i]++;
            next.tuple[j]--;
            iteration++;
        }

    }


    neighbourhood.push(next);
    return neighbourhood;
}

SwitchObjectsLocalizer::SwitchObjectsLocalizer(const Instance &instance, const unsigned int nbrTries) : Localizer(instance),
 nbrTries(nbrTries), nbrObjects(instance.objects.size()), ratios(getRatios()),
           rng(dev()), dist(ratios.begin(), ratios.end())
{
    rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
/*
    const int nrolls=10000;//000;  // number of experiments
    const int nstars=1000;//0;    // maximum number of stars to distribute

    std::map<int, int> hist;
    for (int n = 0; n < nrolls; ++n) {
        ++hist[std::round(dist(rng))];
    }

    for (auto p : hist) {
        std::cout << p.first << " : " << std::string(p.second*nstars/nrolls,'*') << '\n';
    }
    //*/
}


std::vector<double> SwitchObjectsLocalizer::getRatios()
{
    std::vector<double> sortedObjs(nbrObjects);
    for(unsigned int i = 0; i< objects.size();i++)
        sortedObjs.push_back(((double)objects[i].value*1000000)/((double)objects[i].weight));

    std::sort(sortedObjs.begin(), sortedObjs.end(), std::greater<>());
    return sortedObjs;
}


