//
// Created by Jugurtha Chaker on 08/05/2020.
//

#include "Localizer.h"

Objects Localizer::sortObjects() {

    Objects sortedObjs;
    for(unsigned int i = 0; i< objects.size();i++)
        sortedObjs.push_back(Object{objects[i].weight, objects[i].value});

    std::sort(sortedObjs.begin(), sortedObjs.end(),[](const Object & a, const Object & b) -> bool{
        double dav = a.value, daw = a.weight;
        double dbv = b.value, dbw = b.weight;
        return (dav/daw) > (dbv/dbw);

    });

    return sortedObjs;
}

Localizer::Localizer(Instance const& instance) : objects(instance.objects), maxWeight(instance.maxWeight),sorted(false) {
    sortedObjects = sortObjects();
}

int Localizer::sumWeight(Solution const& solution)
{
    int weight(0);
    for (unsigned int i = 0; i < objects.size(); ++i)
        weight += solution.tuple[i] * sortedObjects[i].weight;

    return weight;
}

