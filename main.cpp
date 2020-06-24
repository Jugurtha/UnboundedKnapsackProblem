#include <iostream>
#include <chrono>
#include "BranchAndBound.h"
#include "DatasetReader.h"
#include "Logger.h"
#include "Tabu.h"
#include "AddOneLocalizer.h"
#include "SwitchObjectsLocalizer.h"
#include "Greedy.h"
#include "Genetic.h"
#include "HybridInit.h"
#include "HybridIn.h"
#include "HybridFin.h"
//#include "BranchAndBound01.h"


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
    StoppingConditionNbrIterations stoppingConditionNbrIterations(50);
    FitnessValue fitnessValue;
    AddOneLocalizer localizer(instance);
    Tabu tabu(Solution{std::vector<int>(instance.objects.size(), 0), 0},
            tabuListBestValueSet, 100,
            stoppingConditionNbrIterations, fitnessValue, localizer);

    return tabu.search();
}






int main(int argc, char* argv[]) {

    std::map<std::string, std::string> dataset;
    dataset["FacilePetite"] = "./Datasets/Facile/Petite/FacilePetite.txt";
    dataset["FacileGrande"] = "./Datasets/Facile/Grande/FacileGrande.txt";
    dataset["MoyenneGrande"] = "./Datasets/Moyenne/Grande/MoyenneGrande.txt";
    dataset["MoyennePetite"] = "./Datasets/Moyenne/Petite/MoyennePetite.txt";
    dataset["DifficilePetite"] = "./Datasets/Difficile/Petite/DifficilePetite.txt";
    dataset["DifficileGrande"] = "./Datasets/Difficile/Grande/DifficileGrande.txt";

    std::string algorthm(argv[2]);
    std::string algorthmG01P = "Greedy_Knapsack_Profit";
    std::string algorthmG01D = "Greedy_Knapsack_Density";
    std::string algorthmG01W = "Greedy_Knapsack_Weight";
    std::string algorthmGuP = "Greedy_Unbounded_Knapsack_Profit";
    std::string algorthmGuD = "Greedy_Unbounded_Knapsack_Density";
    std::string algorthmGuW = "Greedy_Knapsack_Unbounded_Weight";
    std::string algorthmGn01 = "Genetic01";//Not set yet
    std::string algorthmGNu = "GeneticKnapsackSolver";
    std::string algorthmHInit = "HybridInitKnapsackSolver";
    std::string algorthmHIn = "HybridInKnapsackSolver";
    std::string algorthmHFin = "HybridFinKnapsackSolver";



    std::string instancePath(dataset[std::string(argv[1])]);
    std::cout << "\n\nInstance : " << instancePath << '\n';
    DatasetReader datasetReader(instancePath);

    auto instance = datasetReader.getInstance();
    std::cout << "n : " << instance.objects.size() << '\n';
    std::cout << "Max weight : " << instance.maxWeight << "\n";
    auto optimalResults = datasetReader.getOptimalResult();
    std::cout << "Optimal value : "<< optimalResults.value << "\nMinimal weight for optimal value : " << optimalResults.weight
              << "\nExecution time : " <<  optimalResults.executionTime*1000 << "\n\n";

    auto start = std::chrono::high_resolution_clock::now();
    auto end  = start;

    int n = instance.objects.size();
    int max = instance.maxWeight;

    std::ofstream outfile("result", std::ios_base::trunc);


    int** item = new int*[n];
    for (int i = 0; i < n; ++i) {
        item[i] = new int[2];
    }
    for (int i = 0; i < n; ++i) {
        item[i][0] = instance.objects[i].value;
        item[i][1] = instance.objects[i].weight;
    }
    Solution greedySolution;

    if(algorthm==algorthmG01P)
    {
        printf("**********************************Greedy_Knapsack_Profit0/1********************************************** \n");
        start = std::chrono::high_resolution_clock::now();
        greedySolution = Greedy_Knapsack_Profit(item, n, max);
        end = std::chrono::high_resolution_clock::now();

        outfile << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() ;
        for(auto e : greedySolution.tuple)
            outfile << '\n' << e ;
    }
    else if(algorthm==algorthmG01W)
    {
        printf("***************************************Greedy_Knapsack_Weight0/1***************************************** \n");
        start = std::chrono::high_resolution_clock::now();
        greedySolution = Greedy_Knapsack_Weight(item, n, max);
        end = std::chrono::high_resolution_clock::now();

        outfile << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() ;
        for(auto e : greedySolution.tuple)
            outfile << '\n' << e ;
    }
    else if(algorthm==algorthmG01D)
    {
        printf("*************************************Greedy_Knapsack_Density0/1******************************************* \n");
        start = std::chrono::high_resolution_clock::now();
        greedySolution = Greedy_Knapsack_Density(item, n, max);
        end = std::chrono::high_resolution_clock::now();

        outfile << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() ;
        for(auto e : greedySolution.tuple)
            outfile << '\n' << e ;;
    }
    else if(algorthm==algorthmGuP)
    {
        printf("***************************************Greedy_Unbounded_Knapsack_Profit***************************************** \n");
        start = std::chrono::high_resolution_clock::now();
        greedySolution = Greedy_Unbounded_Knapsack_Profit(item, n, max);
        end = std::chrono::high_resolution_clock::now();

        outfile << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() ;
        for(auto e : greedySolution.tuple)
            outfile << '\n' << e ;
    }
    else if(algorthm==algorthmGuW)
    {
        printf("******************************************Greedy_Knapsack_Unbounded_Weight**************************************\n");
        start = std::chrono::high_resolution_clock::now();
        greedySolution = Greedy_Knapsack_Unbounded_Weight(item, n, max);
        end = std::chrono::high_resolution_clock::now();

        outfile << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() ;
        for(auto e : greedySolution.tuple)
            outfile << '\n' << e ;
    }
    else if(algorthm==algorthmGuD)
    {
        printf("*************************************Greedy_Unbounded_Knapsack_Density*******************************************\n");
        start = std::chrono::high_resolution_clock::now();
        greedySolution = Greedy_Unbounded_Knapsack_Density(item, n, max);
        end = std::chrono::high_resolution_clock::now();

        outfile << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() ;
        for(auto e : greedySolution.tuple)
            outfile << '\n' << e ;
    }
    else if(algorthm==algorthmGn01)
    {
  /*      std::cout << "--------------------------Genetic Algorithm 0/1----------------------------------------------\n";

        size_t pptsize = std::stoi(argv[3]);
        size_t nbrIterations = std::stoi(argv[4]);
        float crossOver = std::stof(argv[5]);
        float mutation = std::stof(argv[6]);

        std::vector<Item> items;
        for(auto o : instance.objects) {
            Item item1; item1.value = (std::size_t) o.value; item1.weight=o.weight;
            items.push_back(item1);
        }

        auto geneticSolver = Genetic01(
                items,
                instance.maxWeight,  // capacity
                pptsize,     // population size
                nbrIterations,     // iterations
                //crossOver, //crossover probability
                mutation);
        start = std::chrono::high_resolution_clock::now();
        auto geneticResult = geneticSolver.solve();
        end = std::chrono::high_resolution_clock::now();


        outfile << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() ;
        for(auto e : geneticResult.chromosome)
            outfile << '\n' << e ;
   */
    }
    else if(algorthm==algorthmGNu)
    {
        std::cout << "--------------------------Genetic Algorithm unbouned-------------------------------------------------------\n";



        size_t pptsize = std::stoi(argv[3]);
        size_t nbrIterations = std::stoi(argv[4]);
        float crossOver = std::stof(argv[5]);
        float mutation = ((float)std::stoi(argv[6]))/100000;

        std::cout << "pptsize" << pptsize << '\n';
        std::cout << "nbrIterations" << nbrIterations << '\n';
        std::cout << "crossOver" << crossOver << '\n';
        std::cout << "mutation" << mutation << std::endl;

        std::vector<Item> items;
        for(auto o : instance.objects) {
            Item item1 ;item1.weight= o.weight;item1.value=(std::size_t) o.value;
            items.push_back(item1);
        }

        auto geneticSolver = GeneticKnapsackSolver(
                items,
                instance.maxWeight,  // capacity
                pptsize,     // population size
                nbrIterations,     // iterations
                crossOver, //crossover probability
                mutation);
        start = std::chrono::high_resolution_clock::now();
        auto geneticResult = geneticSolver.solve();
        end = std::chrono::high_resolution_clock::now();


        outfile << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() ;
        for(auto e : geneticSolver.getObjects())
            outfile << '\n' << e ;
    }
    else if(algorthm==algorthmHInit)
    {
        std::cout << "--------------------------HybridInit Algorithm-------------------------------------------------------\n";


        size_t pptsize = std::stoi(argv[3]);
        size_t nbrIterations = std::stoi(argv[4]);
        float crossOver = std::stof(argv[5]);
        float mutation = std::stof(argv[6]);
        float pHillClimbing = std::stof(argv[7]);

        std::cout << "pptsize" << pptsize << '\n';
        std::cout << "nbrIterations" << nbrIterations << '\n';
        std::cout << "crossOver" << crossOver << '\n';
        std::cout << "mutation" << mutation << std::endl;
        std::cout << "pHillClimbing" << pHillClimbing << std::endl;

        auto hybridInitSolver = HybridInitKnapsackSolver(
                instance.objects,
                instance.maxWeight,  // capacity
                pptsize,     // population size
                nbrIterations,     // iterations
                crossOver, //crossover probability
                pHillClimbing, //hill probability
                mutation);    // mutation rate
        start = std::chrono::high_resolution_clock::now();
        auto HybridInitResult = hybridInitSolver.solve();
        end = std::chrono::high_resolution_clock::now();

        outfile << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() ;
        for(auto e : hybridInitSolver.getObjects())
            outfile << '\n' << e ;
    }
    else if(algorthm==algorthmHIn)
    {
        std::cout << "--------------------------HybridIn Algorithm-------------------------------------------------------\n";


        size_t pptsize = std::stoi(argv[3]);
        size_t nbrIterations = std::stoi(argv[4]);
        float crossOver = std::stof(argv[5]);
        float mutation = std::stof(argv[6]);
        float pHillClimbing = std::stof(argv[7]);

        std::cout << "pptsize" << pptsize << '\n';
        std::cout << "nbrIterations" << nbrIterations << '\n';
        std::cout << "crossOver" << crossOver << '\n';
        std::cout << "mutation" << mutation << std::endl;
        std::cout << "pHillClimbing" << pHillClimbing << std::endl;

        auto hybridInSolver = HybridInKnapsackSolver(
                instance.objects,
                instance.maxWeight,  // capacity
                pptsize,     // population size
                nbrIterations,     // iterations
                crossOver, //crossover probability
                pHillClimbing, //hill probability
                mutation);    // mutation rate
        start = std::chrono::high_resolution_clock::now();
        auto hybridInResult = hybridInSolver.solve();
        end = std::chrono::high_resolution_clock::now();

        outfile << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() ;
        for(auto e : hybridInSolver.getObjects())
            outfile << '\n' << e ;
    }
    else if(algorthm==algorthmHFin)
    {
        std::cout << "--------------------------HybridFin Algorithm-------------------------------------------------------\n";


        size_t pptsize = std::stoi(argv[3]);
        size_t nbrIterations = std::stoi(argv[4]);
        float crossOver = std::stof(argv[5]);
        float mutation = std::stof(argv[6]);

        std::cout << "pptsize" << pptsize << '\n';
        std::cout << "nbrIterations" << nbrIterations << '\n';
        std::cout << "crossOver" << crossOver << '\n';
        std::cout << "mutation" << mutation << std::endl;

        auto HybridFinSolver = HybridFinKnapsackSolver(
                instance.objects,
                instance.maxWeight,  // capacity
                pptsize,     // population size
                nbrIterations,     // iterations
                crossOver, //crossover probability
                mutation);    // mutation rate
        start = std::chrono::high_resolution_clock::now();
        auto HybridFinResult = HybridFinSolver.solve();
        end = std::chrono::high_resolution_clock::now();

        outfile << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() ;
        for(auto e : HybridFinSolver.getObjects())
            outfile << '\n' << e ;
    }

    //--------------------------Greedy Algorithm--------------------------------------------------------

    //--------------------------Genetic Algorithm--------------------------------------------------------

    //--------------------------HybridInit Algorithm--------------------------------------------------------

    //--------------------------HybridIn Algorithm--------------------------------------------------------

    //--------------------------HybridFin Algorithm--------------------------------------------------------

    return 0;
}

