cmake_minimum_required(VERSION 3.14)
project(UnboundedKnapsackProblem)

set(CMAKE_CXX_STANDARD 14)

add_executable(UnboundedKnapsackProblem main.cpp BranchAndBound.cpp BranchAndBound.h DatasetReader.cpp DatasetReader.h Logger.cpp Logger.h)