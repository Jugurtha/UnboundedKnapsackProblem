#include <iostream>
#include "BranchAndBound.h"
#include "DatasetReader.h"

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
    //DatasetReader datasetReader("./Dataset/Facile/Petite/Facile/Petite.txt");
    DatasetReader datasetReader("C:\\Development\\C++\\TESTS\\OPTIM\\UnboundedKnapsackProblem\\Datasets\\Facile\\Petite\\FacilePetite.txt");
    auto instance = datasetReader.getInstance();
    std::cout << "n : " << instance.objects.size() << "\n";
    std::cout << "Max weight : " << instance.maxWeight << "\n";

    auto sorted = sortObjects(instance.objects);
    for(auto e : sorted)
        std::cout << "Weight : " << e.weight << ", Value : "<< e.value << "\n";

/*    Objects objects{ {10,60}, {20,100}, {30,120}};
    BranchAndBound bb(50,objects);
    auto result = bb.search();
    std::cout << "Value : " << result.value << "\nSet : {\t";
    for(auto e : result.tuple)
        std::cout << e << "\t";
    std::cout << "}";
*/

    BranchAndBound bb(instance.maxWeight, instance.objects);
    auto result = bb.search();
    std::cout << "Value : " << result.value << "\nWeight : " << computeWeight(sorted, result.tuple) << "\nSet : {\n";
    for(auto e : result.tuple)
        std::cout << e << "\n";
    std::cout << "}";

    return 0;
}