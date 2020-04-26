//
// Created by CHAKER Jugurtha on 25/04/2020.
//

#include "BranchAndBound.h"


BranchAndBound::BranchAndBound(unsigned int maxWeight, Objects objects):maxWeight(maxWeight)
{
    for(auto object : objects)
    {
        weights.push_back(object.weight);
        values.push_back(object.value);
    }
}

std::vector<int> BranchAndBound::separate(unsigned int maxWeight, Objects sortedObjects, std::vector<int> tuple) {
    int j = 0;
    for ( auto i : tuple){
        if(i != -1){
            maxWeight -= i*sortedObjects[j].weight;
            j++;
        }
    }

    int maxIndex = 0;
    while ( maxWeight >= ((maxIndex+1)*(sortedObjects[j].weight)) ){
        maxIndex++;
    }

    std::vector<int> returnedArray;
    for(auto i = 0; i<= maxIndex; i++)
        returnedArray.push_back(i);
    return returnedArray;
}


bool BranchAndBound::isASolution(unsigned int maxWeight, Objects sortedObjects,  std::vector<int> tuple) {
    int j = 0;
    for (auto i : tuple){
        maxWeight -= i*sortedObjects[j].weight;
        j++;
    }

    while(j< sortedObjects.size()){
        if ( maxWeight - sortedObjects[j].weight >= 0)
            break;
        else
            j++;
    }
    return j == sortedObjects.size();
}

Evaluation BranchAndBound::evaluate(unsigned int maxWeight, Objects sortedObjects, std::vector<int> tuple) {
    if (isASolution(maxWeight, sortedObjects,tuple)){
        int sum =0;
        for (auto i=0; i<tuple.size(); i++) {
            sum += tuple[i]*sortedObjects[i].value;
        }

        while (tuple.size() < sortedObjects.size())
            tuple.push_back(0);
        return Evaluation{true, sum,tuple};
    }

    int j = 0;
    int sum = 0;
    for ( auto i : tuple){
        maxWeight -= i* sortedObjects[j].weight;
        sum += i* sortedObjects[j].value;
        j++;
    }

    sum += (maxWeight/sortedObjects[j].weight)* sortedObjects[j].value;
    return Evaluation{false, sum,tuple};
}

Objects BranchAndBound::sortObjects() {

    Objects sortedObjs;
    for(int i = 0; i< weights.size();i++)
        sortedObjs.push_back(Object{weights[i], values[i]});

    std::sort(sortedObjs.begin(), sortedObjs.end(),[](const Object & a, const Object & b) -> bool{ return a.value/a.weight > b.value/b.weight;});
    //for(auto e :sortedObjs)
    //    std::cout << "{" << e.value << ", " << e.weight << "} = " << e.value/e.weight << "\n";
    return sortedObjs;
}

Solution BranchAndBound::findSolution(unsigned int maxWeight, Objects sortedObjects) {
    int objIndex = 0;
    int val = 0;
    std::vector<int> tuple = std::vector<int>(sortedObjects.size(), 0);
    while (objIndex < sortedObjects.size()){
        if (maxWeight >= sortedObjects[objIndex].weight){
            maxWeight -= sortedObjects[objIndex].weight;
            val += sortedObjects[objIndex].value;
            tuple[objIndex]++;
        } else
            objIndex++;
    }
    return Solution{tuple, val};
}

Solution BranchAndBound::search() {
    std::vector<Node> nodes;
    auto sortedObjects = sortObjects();
    auto ActualSolution = findSolution (maxWeight, sortedObjects);
    std::vector<int> tuple{-1};
    auto separationArray = separate(maxWeight, sortedObjects, tuple);
    for (auto i : separationArray)
    {
        tuple[0]=i;
        auto evaluation = evaluate(maxWeight, sortedObjects,tuple);
        if (evaluation.isAsolution)
        {
            if (evaluation.value > ActualSolution.value)
            {
                ActualSolution.value = evaluation.value;
                ActualSolution.tuple = evaluation.tuple;
            }
        } else {
            if ( evaluation.value >= ActualSolution.value+1)
                nodes.push_back (Node{
                        0,
                        tuple,
                        evaluation.value
                });
        }
    }

    while (nodes.size()){
        auto activeNode = nodes.back();
        nodes.pop_back();
        if(activeNode.eval >= ActualSolution.value+1){
            tuple = activeNode.tuple;
            tuple.push_back(-1);
            separationArray = separate(maxWeight, sortedObjects, tuple);
            for (auto i : separationArray){
                tuple[activeNode.depth+1] = i;
                auto evaluation = evaluate(maxWeight, sortedObjects,tuple);
                if (evaluation.isAsolution) {
                    if (evaluation.value > ActualSolution.value){
                        ActualSolution.value = evaluation.value;
                        ActualSolution.tuple = evaluation.tuple;
                    }
                } else {
                    if (evaluation.value > ActualSolution.value+1)
                        nodes.push_back(Node{
                                activeNode.depth + 1,
                                tuple,
                                evaluation.value
                        });
                }
            }
        }
    }
    return ActualSolution;
}


