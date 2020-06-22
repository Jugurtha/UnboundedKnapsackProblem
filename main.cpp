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
#include "BranchAndBound01.h"


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
/*
    std::string instancePath("../Datasets/demoinstancetest.txt");
    //std::string instancePath("../Datasets/Facile/Petite/FacilePetite.txt");
    //std::string instancePath("../Datasets/Difficile/Petite/DifficilePetite.txt");
    //std::string instancePath("../Datasets/Moyenne/Petite/MoyennePetite.txt");
    //std::string instancePath("../Datasets/exnsdbis10.ukp");
    //std::string instancePath("../Datasets/exnsds12.ukp");
    //std::string instancePath("../Datasets/exnsd16.ukp");
    //std::string instancePath("../Datasets/exnsd18.ukp");
    //std::string instancePath("../Datasets/exnsdbis18.ukp");
    //std::string instancePath("../Datasets/exnsd20.ukp");
    //std::string instancePath("../Datasets/exnsd26.ukp");
//*/
    std::map<std::string, std::string> dataset;
/*  dataset["demoinstancetest"] = "../Datasets/demoinstancetest.txt";
    dataset["FacilePetite"] = "../Datasets/Facile/Petite/FacilePetite.txt";
    dataset["FacileGrande"] = "../Datasets/Facile/Grande/FacileGrande.txt";
    dataset["MoyenneGrande"] = "../Datasets/Moyenne/Grande/MoyenneGrande.txt";
    dataset["MoyennePetite"] = "../Datasets/Moyenne/Petite/MoyennePetite.txt";
*/    dataset["DifficilePetite"] = "../Datasets/Difficile/Petite/DifficilePetite.txt";
    dataset["DifficileGrande"] = "../Datasets/Difficile/Grande/DifficileGrande.txt";
//*/
/*
    dataset["exnsdbis10"] = "../Datasets/exnsdbis10.ukp";
 //   dataset["exnsds12"] = "../Datasets/exnsds12.ukp";
    dataset["exnsd16"] = "../Datasets/exnsd16.ukp";
    dataset["exnsd18"] = "../Datasets/exnsd18.ukp";
    dataset["exnsdbis18"] = "../Datasets/exnsdbis18.ukp";
    dataset["exnsd20"] = "../Datasets/exnsd20.ukp";
    dataset["exnsd26"] = "../Datasets/exnsd26.ukp";
//*/

    for(auto e : dataset){

        //std::string instancePath(dataset["demoinstancetest"]);
        std::string instancePath(e.second);
        std::cout << "\n\nInstance : " << instancePath << '\n';
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

        TabuListBestValueSet tabuListBestValueSet;
        FitnessValue fitnessValue;
        TabuType type;
        Solution initSol;
        AddOneLocalizer addOneLocalizer(instance);

        std::vector<int> testsNbrTrials{500};//std::vector<int> testsNbrTrials{50, 100, 250, 500, 1000};
        std::vector<int> testsMaxTabuSize{500};//std::vector<int> testsMaxTabuSize{50, 100, 250, 500, 1000};
        std::vector<int> testsMaxNbrIterations{500};//std::vector<int> testsMaxNbrIterations{50, 100, 250, 500, 1000};
        for(auto nbrTrials : testsNbrTrials)
            for(auto maxTabuSize : testsMaxTabuSize)
                for(auto maxNbrIterations : testsMaxNbrIterations)
                {
                    //int nbrTrials = 50;//50 100 250 500 1000
                    //int maxTabuSize = 100;//50 100 250 500 1000
                    //int maxNbrIterations = 50;//50 100 250 500 1000

                    SwitchObjectsLocalizer switchObjectsLocalizer(instance, nbrTrials);
                    Localizer* localizer = NULL;

                    for(auto t = 0; t<TabuType::NBR_TYPES; t++){

                        std::string parameters;
                        parameters.clear();
                        switch(t)
                        {
                            case ADD_ONE:
//*
                                type = TabuType::ADD_ONE;
                                localizer = &addOneLocalizer;
                                initSol = Solution{std::vector<int>( instance.objects.size(), 0), 0};
                                parameters = std::to_string(maxTabuSize) + "," + std::to_string(maxNbrIterations);
//*/
                                break;

                            case SWITCH_OBJ:
//*
                                type = TabuType::SWITCH_OBJ;
                                localizer = &switchObjectsLocalizer;
                                initSol = initSolution(instance);
                                parameters = std::to_string(maxTabuSize) + "," +std::to_string(maxNbrIterations)+ "," + std::to_string(nbrTrials);
//*/
                                break;

                            default:
                                std::cout << "Tabu search type not recognised\n";
                                exit(EXIT_FAILURE);
                                break;
                        }

                        StoppingConditionNbrIterations stoppingCondition(maxNbrIterations);

                        Tabu tabu(  initSol,
                                    tabuListBestValueSet, maxTabuSize,
                                    stoppingCondition, fitnessValue, *localizer);

                        auto start = std::chrono::high_resolution_clock::now();

                        auto solution = tabu.search();

                        auto end = std::chrono::high_resolution_clock::now();

                        Result result;
                        result.value = solution.value;
                        result.weight = computeWeight(sorted, solution.tuple);
                        result.executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                        parameters;//-------------------------------------------------------
                        Logger logger("log_final2.csv");
                        logger.log(type, instancePath, optimalResults, result, parameters);

                        std::cout << "\nType : " << TABU_TYPE_STRING[t] << "\n";
                        std::cout << "\nValue : " << result.value << "\nWeight : " <<  result.weight << "\nExecution time : " <<  result.executionTime;
                        std::cout << "\n\nRatio values : " << double(result.value) / double(optimalResults.value) * 100 << "%" <<
                                  "\nRatio weights : " << double(result.weight) / double(optimalResults.weight) *100 << "%" <<
                                  "\nRatio execution time : " << result.executionTime /  optimalResults.executionTime*1000 *100 << "%" <<'\n';
//*
                        std::cout << "\nSet : {";
                        for(auto e : solution.tuple)
                            std::cout << e << " ";
                        std::cout << "}" << std::endl;
//*/
                }


        }
//*
        /*        auto start = std::chrono::high_resolution_clock::now();
              auto end  = start;
              //--------------------------Branch And Bound-------------------------------------------------------
              std::cout << "--------------------------Branch And Bound Unbounded---------------------------------------------------\n";
              /*
                     BranchAndBound bb(instance.maxWeight, instance.objects);
                     start = std::chrono::high_resolution_clock::now();
                     auto resultBb = bb.search();
                     end = std::chrono::high_resolution_clock::now();

                     std::cout << "\nTime : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                     std::cout << "\nSet : {";
                     for(auto e : resultBb.tuple)
                         std::cout << e << " ";
                     std::cout << "}" << std::endl;

                     std::cout << "--------------------------Branch And Bound 0/1-------------------------------------------------------\n";

                     BranchAndBound01 bb01(instance.maxWeight, instance.objects.data(),instance.objects.size());
                     start = std::chrono::high_resolution_clock::now();
                     auto resultbb01 = bb01.knapsack();
                     end = std::chrono::high_resolution_clock::now();

                     std::cout << "\nTime : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                     std::cout << "\nSet : {";
                     for(auto e : resultbb01.tuple)
                         std::cout << e << " ";
                     std::cout << "}" << std::endl;


              //--------------------------Hill Climbing----------------------------------------------------------
              std::cout << "--------------------------Hill Climbing-------------------------------------------------------\n";

              HillClimbing hb(instance.maxWeight, instance.objects);
              int iterations=100;
              start = std::chrono::high_resolution_clock::now();
              auto result_HillClimbing= hb.Run(iterations);
              end = std::chrono::high_resolution_clock::now();

              std::cout << "\nTime : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
              std::cout << "\nSet : {";
              for(auto e : result_HillClimbing.tuple)
                  std::cout << e << " ";
              std::cout << "}" << std::endl;

              //--------------------------Greedy Algorithm--------------------------------------------------------
              std::cout << "--------------------------Greedy Algorithm-------------------------------------------------------\n";

              int n = instance.objects.size();
              int max = instance.maxWeight;
              int** item = new int*[n];
              for (int i = 0; i < n; ++i) {
                  item[i] = new int[2];
              }
              for (int i = 0; i < n; ++i) {
                  item[i][0] = instance.objects[i].value;
                  item[i][1] = instance.objects[i].weight;
              }
              Solution greedySolution;

              printf("**********************************Greedy_Knapsack_Profit0/1********************************************** \n");
              start = std::chrono::high_resolution_clock::now();
              greedySolution = Greedy_Knapsack_Profit(item, n-1, max);
              end = std::chrono::high_resolution_clock::now();

              std::cout << "\nTime : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
              std::cout << "\nSet : {";
              for(auto e : greedySolution.tuple)
                  std::cout << e << " ";
              std::cout << "}" << std::endl;

              printf("***************************************Greedy_Knapsack_Weight0/1***************************************** \n");
              start = std::chrono::high_resolution_clock::now();
              greedySolution = Greedy_Knapsack_Weight(item, n-1, max);
              end = std::chrono::high_resolution_clock::now();

              std::cout << "\nTime : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
              std::cout << "\nSet : {";
              for(auto e : greedySolution.tuple)
                  std::cout << e << " ";
              std::cout << "}" << std::endl;

              printf("*************************************Greedy_Knapsack_Density0/1******************************************* \n");
              start = std::chrono::high_resolution_clock::now();
              greedySolution = Greedy_Knapsack_Density(item, n-1, max);
              end = std::chrono::high_resolution_clock::now();

              std::cout << "\nTime : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
              std::cout << "\nSet : {";
              for(auto e : greedySolution.tuple)
                  std::cout << e << " ";
              std::cout << "}" << std::endl;

              printf("***************************************Greedy_Unbounded_Knapsack_Profit***************************************** \n");
              start = std::chrono::high_resolution_clock::now();
              greedySolution = Greedy_Unbounded_Knapsack_Profit(item, n-1, max);
              end = std::chrono::high_resolution_clock::now();

              std::cout << "\nTime : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
              std::cout << "\nSet : {";
              for(auto e : greedySolution.tuple)
                  std::cout << e << " ";
              std::cout << "}" << std::endl;

              printf("******************************************Greedy_Knapsack_Unbounded_Weight**************************************\n");
              start = std::chrono::high_resolution_clock::now();
              greedySolution = Greedy_Knapsack_Unbounded_Weight(item, n-1, max);
              end = std::chrono::high_resolution_clock::now();

              std::cout << "\nTime : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
              std::cout << "\nSet : {";
              for(auto e : greedySolution.tuple)
                  std::cout << e << " ";
              std::cout << "}" << std::endl;

              printf("*************************************Greedy_Unbounded_Knapsack_Density*******************************************\n");
              start = std::chrono::high_resolution_clock::now();
              greedySolution = Greedy_Unbounded_Knapsack_Density(item, n-1, max);
              end = std::chrono::high_resolution_clock::now();

              std::cout << "\nTime : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
              std::cout << "\nSet : {";
              for(auto e : greedySolution.tuple)
                  std::cout << e << " ";
              std::cout << "}" << std::endl;

              //--------------------------Genetic Algorithm--------------------------------------------------------
              std::cout << "--------------------------Genetic Algorithm-------------------------------------------------------\n";

              size_t pptsize = 10;
              std::vector<Item> items;
              for(auto o : instance.objects)
                  items.push_back({o.weight, (std::size_t )o.value});

              auto geneticSolver = GeneticKnapsackSolver(
                      items,
                      instance.maxWeight,  // capacity
                      pptsize,     // population size
                      50,     // iterations
                      0.9, //crossover probability
                      0.00005);
              start = std::chrono::high_resolution_clock::now();
              auto geneticResult = geneticSolver.solve();
              end = std::chrono::high_resolution_clock::now();


              std::cout << "\nValue : " << geneticResult.fitness;
              std::cout << "\nTime : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
              std::cout << "\nSet : {";
              for(auto e : geneticSolver.getObjects())
                  std::cout << e << " ";
              std::cout << "}" << std::endl;


              //--------------------------HybridInit Algorithm--------------------------------------------------------
              std::cout << "--------------------------HybridInit Algorithm-------------------------------------------------------\n";

              pptsize = 10;
              auto hybridInitSolver = HybridInitKnapsackSolver(
                      instance.objects,
                      instance.maxWeight,  // capacity
                      pptsize,     // population size
                      50,     // iterations
                      0.9, //crossover probability
                      0.3, //hill probability
                      0.00005);    // mutation rate
              start = std::chrono::high_resolution_clock::now();
              auto HybridInitResult = hybridInitSolver.solve();
              end = std::chrono::high_resolution_clock::now();

              std::cout << "\nTime : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
              std::cout << "\nSet : {";
              for(auto e : HybridInitResult.chromosome)
                  std::cout << e << " ";
              std::cout << "}" << std::endl;

              //--------------------------HybridIn Algorithm--------------------------------------------------------
              std::cout << "--------------------------HybridIn Algorithm-------------------------------------------------------\n";

              pptsize = 10;
              auto hybridInSolver = HybridInKnapsackSolver(
                      instance.objects,
                      instance.maxWeight,  // capacity
                      pptsize,     // population size
                      50,     // iterations
                      0.9, //crossover probability
                      0.3, //hill probability
                      0.00005);    // mutation rate
              start = std::chrono::high_resolution_clock::now();
              auto hybridInResult = hybridInSolver.solve();
              end = std::chrono::high_resolution_clock::now();

              std::cout << "\nTime : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
              std::cout << "\nSet : {";
              for(auto e : hybridInResult.chromosome)
                  std::cout << e << " ";
              std::cout << "}" << std::endl;

              //--------------------------HybridFin Algorithm--------------------------------------------------------
              std::cout << "--------------------------HybridFin Algorithm-------------------------------------------------------\n";

              pptsize = 10;
              auto HybridFinSolver = HybridFinKnapsackSolver(
                      instance.objects,
                      instance.maxWeight,  // capacity
                      pptsize,     // population size
                      50,     // iterations
                      0.9, //crossover probability
                      0.00005);    // mutation rate
              start = std::chrono::high_resolution_clock::now();
              auto HybridFinResult = HybridFinSolver.solve();
              end = std::chrono::high_resolution_clock::now();

              std::cout << "\nTime : " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
              std::cout << "\nSet : {";
              for(auto e : HybridFinResult.chromosome)
                  std::cout << e << " ";
              std::cout << "}" << std::endl;
      */
    }





    return 0;
}

