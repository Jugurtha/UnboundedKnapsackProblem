//
// Created by LENOVO on 18/06/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_HYBRIDINIT_H
#define UNBOUNDEDKNAPSACKPROBLEM_HYBRIDINIT_H

#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <string>
#include <functional>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <limits>
#include "DatasetReader.h"
#include "HillClimbing.h"




using std::vector;
using std::size_t;
using chromosome_t = vector<int>;
using population_t = vector<chromosome_t>;


class HybridInitKnapsackSolver
{
    struct Solution_g
    {
        chromosome_t chromosome;
        int      fitness;
    };


public:
    int n;
    vector<int> sizes;
    int c;

    HybridInitKnapsackSolver(
            vector<Object> items,
            int       capacity,
            int       population_size,
            int       iterations,
            float		 pc,
            float		 ph,
            float        mutation_rate);
    const Solution_g& solution() const;
    auto solve() -> decltype(solution());
    vector<Object> getItems();


        private:
    vector<Object> items_;
    int          capacity_;
    population_t population_;
    int          iterations_;
    float        mutation_rate_;
    float		 pc_;
    float		 ph_;
    Solution_g     solution_;

    mutable std::default_random_engine rng;


    static bool compare(const Object &a, const Object &b);
    unsigned countBits(unsigned int number);
    void convertToBinary(int n);
    chromosome_t generate_chromosome() const;
    int evaluate(const chromosome_t& chromosome) const;
    const chromosome_t& select(const vector<int>& fitnesses, int max) const;
    void mutate(chromosome_t& chromosome);
    chromosome_t crossover(
            const chromosome_t& chromosome_1,
            const chromosome_t& chromosome_2);
    int weight(const chromosome_t& chromosome) const;


};


#endif //UNBOUNDEDKNAPSACKPROBLEM_HYBRIDINIT_H
