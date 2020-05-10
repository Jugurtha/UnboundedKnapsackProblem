//
// Created by LENOVO on 08/05/2020.
//

#include "AddOneLocalizer.h"



Neighbourhood AddOneLocalizer::getNeighbors(Solution const& center) {
    Neighbourhood neighbourhood;
    Solution next(center);

    for (unsigned int i = 0; i < center.tuple.size(); ++i) {
        next.tuple[i]++;
        if(sumWeight(next)<=maxWeight)
        {
            next.value += sortedObjects[i].value;
            break;
        }
        else
            next.tuple[i]--;

    }
    neighbourhood.push(next);
    return neighbourhood;
}



AddOneLocalizer::AddOneLocalizer(const Instance &instance) : Localizer(instance) {}

/*
int AddOneLocalizer::selectObject(std::unordered_set<Object> excluded) {
    bool found = false;
    int object = 0;
    while (!found)
    {
        if(excluded.count(sortedObjects()[object]))
            found = true;
        else
            object++;
    }
    return object;
}
*/

