
// Created by BENKACI ASMA on 30/04/2020 TP OPTIM HEURISTIQUE VOISINAGE RECHERCHE LOCALE HILL CLIMBING


#ifndef HILL_CLIMBING
#define HILL_CLIMBING

#include <vector>
#include <tuple>
#include <map>
#include <algorithm>
#include <iostream>
#include "../Hill Climbing/HillClimbing_UnboundedKnapsack/commun.h"

class HillClimbing {
public:
    HillClimbing(unsigned int maxWeight, Objects objects);
   std::vector<int> Initial_solution();
    std::vector<int> Ajout(std::vector<int> &solution, int indice);
    int Evaluation(std::vector<int> &solution);
    Solution Determination(Solution candidata, Solution global);
    void print_solution(Solution candidata);
    Solution Run(Solution optimale,int rounds);


public:
    unsigned int maxWeight;
    std::vector<int> weights;
    std::vector<int> values;
	// int rounds;
      //  int iterations;


};

#endif
