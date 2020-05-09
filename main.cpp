#include <iostream>
#include <chrono>
#include "BranchAndBound.h"
#include "DatasetReader.h"
#include "Logger.h"
#include "Tabu.h"
#include "AddOneLocalizer.h"

Objects sortObjects(Objects const&  objs) {
    Objects sortedObjs;
    for(auto o : objs)
        sortedObjs.push_back(o);
    std::sort(sortedObjs.begin(), sortedObjs.end(),[](const Object & a, const Object & b) -> bool{
        double dav = a.value, daw = a.weight;
        double dbv = b.value, dbw = b.weight;
        return (dav/daw) > (dbv/dbw);

    });

    return sortedObjs;
}

int computeWeight(Objects const& orderedObj, std::vector<int> const& tuple)
{
    int weight = 0;
    for(auto i =0; i < orderedObj.size();i++)
        weight += orderedObj[i].weight*tuple[i];
    return weight;
}

int main() {
    
    std::string instancePathAghilas("../../ASMA/demoinstancetest.txt");
    //auto instanceCours = Instance{130,{{33,4},{49,5},{60,6},{32,2}}};
    //std::string instancePath("../Datasets/Facile/Petite/FacilePetite.txt");
    std::string instancePath(instancePathAghilas);
    std::cout << "Instance : " << instancePath << '\n';
    DatasetReader datasetReader(instancePath);
    //auto instance = instanceCours;
    auto instance = datasetReader.getInstance();
    std::cout << "n : " << instance.objects.size() << '\n';
    std::cout << "Max weight : " << instance.maxWeight << "\n\n";

    auto sorted = sortObjects(instance.objects);
//*
    for(auto e : sorted)
        std::cout << "Weight : " << e.weight << ", Value : "<< e.value << '\n';
//*/

    BranchAndBound bb(instance.maxWeight, instance.objects);
    auto result = bb.search();
    auto weight = computeWeight(sorted, result.tuple);
    std::cout << "\nOptimal Solution :\nValue : " << result.value << "\nWeight : " <<  weight << '\n';

    TabuListBestValueSet tabuListBestValueSet;
    StoppingConditionNbrIterations stoppingConditionNbrIterations(10);
    FitnessValue fitnessValue;
    AddOneLocalizer addOneLocalizer(instance);
    Tabu tabu(Solution{std::vector<int>(instance.objects.size(), 0), 0},
            tabuListBestValueSet, 100,
            stoppingConditionNbrIterations, fitnessValue, addOneLocalizer);

    auto start = std::chrono::high_resolution_clock::now();

    result = tabu.search();
    auto end = std::chrono::high_resolution_clock::now();

    weight = computeWeight(sorted, result.tuple);
    Logger logger("log.csv");
    logger.log(instancePath, result.value, weight, std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count());


    std::cout << "\nValue : " << result.value << "\nWeight : " <<  weight;
    std::cout << "\nSet : {";
    for(auto e : result.tuple)
       std::cout << e << " ";
    std::cout << "}";

    return 0;
}