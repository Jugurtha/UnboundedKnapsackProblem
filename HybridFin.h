//
// Created by LENOVO on 18/06/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_HYBRIDFIN_H
#define UNBOUNDEDKNAPSACKPROBLEM_HYBRIDFIN_H


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


class HybridFinKnapsackSolver
{
public:
    struct Solution_g
    {
        chromosome_t chromosome;
        size_t       fitness;
    };

    HybridFinKnapsackSolver(
            vector<Object> items,
            size_t       capacity,
            size_t       population_size,
            size_t       iterations,
            float		 pc,
            float        mutation_rate);
    const Solution_g& solution() const;
    auto solve() -> decltype(solution());
    vector<Object> getItems();


private:
    static bool compare(const Object &a, const Object &b);
    unsigned countBits(unsigned int number);
    void convertToBinary(int n);
    chromosome_t generate_chromosome() const;
    size_t evaluate(const chromosome_t& chromosome) const;
    const chromosome_t& select(const vector<size_t>& fitnesses, size_t max) const;
    void mutate(chromosome_t& chromosome);
    chromosome_t crossover(
            const chromosome_t& chromosome_1,
            const chromosome_t& chromosome_2);
    size_t weight(const chromosome_t& chromosome) const;




public:
    int c;
    std::size_t n;
    vector<int> sizes;




private:
    vector<Object> items_;
    size_t       capacity_;
    population_t population_;
    size_t       iterations_;
    float        mutation_rate_;
    float pc_;
    Solution_g     solution_;

    mutable std::default_random_engine rng;
};



#endif //UNBOUNDEDKNAPSACKPROBLEM_HYBRIDFIN_H
