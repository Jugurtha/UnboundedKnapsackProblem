cmake_minimum_required(VERSION 3.14)
project(UnboundedKnapsackProblem)

set(CMAKE_CXX_STANDARD 14)

add_executable(UnboundedKnapsackProblem main.cpp BranchAndBound.cpp BranchAndBound.h DatasetReader.cpp DatasetReader.h Logger.cpp Logger.h commun.h Tabu.cpp Tabu.h Neighbourhood.h TabuList.cpp TabuList.h Localizer.h Fitness.h StoppingCondition.h Localizer.cpp AddOneLocalizer.cpp AddOneLocalizer.h)