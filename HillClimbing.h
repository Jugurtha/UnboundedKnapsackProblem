
// Created by BENKACI ASMA on 30/04/2020 TP OPTIM HEURISTIQUE VOISINAGE RECHERCHE LOCALE HILL CLIMBING

#ifndef HillClimbing_H
#define HillClimbing_H

#include <vector>
#include <tuple>
#include <map>
#include <algorithm>
#include <iostream>
#include "commun.h"

class HillClimbing {
public:
    HillClimbing(unsigned int maxWeight, Objects objects);
   std::vector<int> Initial_solution();
    std::vector<int> Ajout(std::vector<int> &solution, int indice);
    int Evaluation(std::vector<int> &solution);
    Solution Determination(Solution candidata, Solution global);
    void print_solution(Solution candidata);
    Solution Run(int rounds);


public:
    unsigned int maxWeight;
    std::vector<int> weights;
    std::vector<int> values;
	// int rounds;
      //  int iterations;


};

#endif
