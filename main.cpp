#include <iostream>
#include <chrono>
#include "BranchAndBound.h"
#include "DatasetReader.h"
#include "Logger.h"

Objects sortObjects(Objects const&  objs) {
    Objects sortedObjs;
    for(auto o : objs)
        sortedObjs.push_back(o);

    std::sort(sortedObjs.begin(), sortedObjs.end(),[](const Object & a, const Object & b) -> bool{ return a.value/a.weight > b.value/b.weight;});
    //for(auto e :sortedObjs)
    //    std::cout << "{" << e.value << ", " << e.weight << "} = " << e.value/e.weight << "\n";
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
    std::cout << "Hello, World!" << std::endl;
    std::string instancePath("C:\\Development\\C++\\TESTS\\OPTIM\\ASMA\\demoinstancetest.txt");
    DatasetReader datasetReader(instancePath);
    auto instance = datasetReader.getInstance();
    std::cout << "n : " << instance.objects.size() << "\n";
    std::cout << "Max weight : " << instance.maxWeight << "\n";

    auto sorted = sortObjects(instance.objects);
//*
    for(auto e : sorted)
        std::cout << "Weight : " << e.weight << ", Value : "<< e.value << "\n";
//*/

    BranchAndBound bb(instance.maxWeight, instance.objects);

    auto start = std::chrono::high_resolution_clock::now();
    auto result = bb.search();
    auto end = std::chrono::high_resolution_clock::now();

    auto weight = computeWeight(sorted, result.tuple);
    Logger logger("log.csv");
    logger.log(instancePath, result.value, weight, std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count());


    std::cout << "Value : " << result.value << "\nWeight : " <<  weight;
    std::cout << "\nSet : {\n";
    for(auto e : result.tuple)
       std::cout << e << "\n";
    std::cout << "}";

    return 0;
}