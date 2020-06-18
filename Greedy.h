//
// Created by LENOVO on 18/06/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_GREEDY_H
#define UNBOUNDEDKNAPSACKPROBLEM_GREEDY_H

#include<iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include<vector>
#include "commun.h"


Solution Greedy_Knapsack_Profit(int **item, int n, int max);
Solution Greedy_Unbounded_Knapsack_Profit(int **item, int n, int max);
Solution Greedy_Knapsack_Weight(int **item, int n, int max);
Solution Greedy_Knapsack_Unbounded_Weight(int **item, int n, int max);
Solution Greedy_Knapsack_Density(int **item, int n, int max);
Solution Greedy_Unbounded_Knapsack_Density(int **item, int n, int max);



#endif //UNBOUNDEDKNAPSACKPROBLEM_GREEDY_H
