cmake_minimum_required(VERSION 3.14)
project(UnboundedKnapsackProblem)

set(CMAKE_CXX_STANDARD 14)

add_executable(UnboundedKnapsackProblem main.cpp BranchAndBound.cpp BranchAndBound.h DatasetReader.cpp DatasetReader.h Logger.cpp Logger.h commun.h Tabu.cpp Tabu.h Neighbourhood.h TabuList.cpp TabuList.h Localizer.h Fitness.h StoppingCondition.h Localizer.cpp AddOneLocalizer.cpp AddOneLocalizer.h SwitchObjectsLocalizer.cpp SwitchObjectsLocalizer.h HillClimbing.h HillClimbing.cpp Greedy.h Greedy.cpp Genetic.h Genetic.cpp HybridInit.cpp HybridInit.h HybridIn.h HybridIn.cpp HybridFin.h HybridFin.cpp BranchAndBound01.cpp BranchAndBound01.h)
# add_library(Knapsack STATIC BranchAndBound.cpp DatasetReader.cpp Logger.cpp Tabu.cpp TabuList.cpp Localizer.cpp AddOneLocalizer.cpp SwitchObjectsLocalizer.cpp HillClimbing.cpp Greedy.cpp Genetic.cpp HybridInit.cpp HybridIn.cpp HybridFin.cpp BranchAndBound01.cpp)