#include <iostream>
#include <chrono>
#include "BranchAndBound.h"
#include "DatasetReader.h"
#include "Logger.h"
#include "Tabu.h"
#include "AddOneLocalizer.h"
#include "SwitchObjectsLocalizer.h"

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
    for(unsigned int i =0; i < orderedObj.size();i++)
        weight += orderedObj[i].weight*tuple[i];
    return weight;
}

Solution initSolution(Instance const& instance)
{
    TabuListBestValueSet tabuListBestValueSet;
    StoppingConditionNbrIterations stoppingConditionNbrIterations(200);
    FitnessValue fitnessValue;
    AddOneLocalizer localizer(instance);
    Tabu tabu(Solution{std::vector<int>(instance.objects.size(), 0), 0},
            tabuListBestValueSet, 100,
            stoppingConditionNbrIterations, fitnessValue, localizer);

    return tabu.search();
}

int main() {

    //std::string instancePath("../Datasets/demoinstancetest.txt");
    //std::string instancePath("../Datasets/Facile/Petite/FacilePetite.txt");
    //std::string instancePath("../Datasets/Difficile/Petite/DifficilePetite.txt");
    //std::string instancePath("../Datasets/Moyenne/Petite/MoyennePetite.txt");
    //std::string instancePath("../Datasets/exnsdbis10.ukp");
    //std::string instancePath("../Datasets/exnsds12.ukp");
    std::string instancePath("../Datasets/exnsd16.ukp");
    //std::string instancePath("../Datasets/exnsd18.ukp");
    //std::string instancePath("../Datasets/exnsdbis18.ukp");
    //std::string instancePath("../Datasets/exnsd20.ukp");
    //std::string instancePath("../Datasets/exnsd26.ukp");
    std::cout << "Instance : " << instancePath << '\n';
    DatasetReader datasetReader(instancePath);
/*
    auto instanceCours = Instance{130,{{33,4},{49,5},{60,6},{32,2}}};
    auto instance = instanceCours;
//*/
    auto instance = datasetReader.getInstance();
    std::cout << "n : " << instance.objects.size() << '\n';
    std::cout << "Max weight : " << instance.maxWeight << "\n";
    auto optimalResults = datasetReader.getOptimalResult();
    std::cout << "Optimal value : "<< optimalResults.value << "\nMinimal weight for optimal value : " << optimalResults.weight
     << "\nExecution time : " <<  optimalResults.executionTime*1000 << "\n\n";


    auto sorted = sortObjects(instance.objects);
/*
    std::cout << "Main : -----------------------------------------\n";
    for(auto e : sorted)
        std::cout << "Weight : " << e.weight << ", Value : "<< e.value << '\n';
    std::cout << "Main : -----------------------------------------\n";
//*/
/*
    BranchAndBound bb(instance.maxWeight, instance.objects);
    auto exactSolution = bb.search();
    auto weight = computeWeight(sorted, exactSolution.tuple);
    std::cout << "\nOptimal Solution :\nValue : " << exactSolution.value << "\nWeight : " <<  weight << '\n';
    std::cout << "\nValue : " << exactSolution.value << "\nWeight : " <<  weight;
    std::cout << "\nSet : {";
    for(auto e : exactSolution.tuple)
       std::cout << e << " ";
    std::cout << "}\n\n";
//*/
    TabuListBestValueSet tabuListBestValueSet;
    StoppingConditionNbrIterations stoppingConditionNbrIterations(500);
    FitnessValue fitnessValue;
//*
    AddOneLocalizer localizer(instance);
    auto initSol = Solution{std::vector<int>( instance.objects.size(), 0), 0};
//*/
/*
    SwitchObjectsLocalizer localizer(instance, 1000);// ------------------------------------------------
    auto initSol = initSolution(instance);
//*/
    Tabu tabu(  initSol,
                tabuListBestValueSet, 100,
                stoppingConditionNbrIterations, fitnessValue, localizer);

    auto start = std::chrono::high_resolution_clock::now();

    auto solution = tabu.search();

    auto end = std::chrono::high_resolution_clock::now();

    Result result;
    result.value = solution.value;
    result.weight = computeWeight(sorted, solution.tuple);
    result.executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    Logger logger("log.csv");
    logger.log(instancePath, optimalResults, result);


    std::cout << "\nValue : " << result.value << "\nWeight : " <<  result.weight << "\nExecution time : " <<  result.executionTime;
    std::cout << "\n\nDelta values : " << optimalResults.value - result.value <<
    "\nDelta weights : " << optimalResults.weight - result.weight <<
    "\nDelta execution time : " << optimalResults.executionTime*1000 - result.executionTime << '\n';
//*
    std::cout << "\nSet : {";
    for(auto e : solution.tuple)
       std::cout << e << " ";
    std::cout << "}";
//*/

    return 0;
}
