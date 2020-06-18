#pragma once


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
#include "Genetic.h"



using std::vector;
using std::size_t;
using chromosome_t = vector<int>;
using population_t = vector<chromosome_t>;


struct Item
{
    size_t weight;
    size_t value;
};



class GeneticKnapsackSolver{
public:

    GeneticKnapsackSolver(
            vector<Item> items,
            size_t       capacity,
            size_t       population_size,
            size_t       iterations,
            float		 pc,
            float        mutation_rate)

            : items_{ std::move(items) }
            , capacity_{ capacity }
            , population_(population_size)
            , iterations_{ iterations }
            , mutation_rate_{ mutation_rate }
            ,pc_ {pc }
            , solution_{ chromosome_t(n, {}), 0 }
            , rng{ []{const auto seed = std::random_device{}();return seed;}() }
    {

    }

    struct Solution
    {
        chromosome_t chromosome;
        size_t       fitness;
    };
    int c;
    std::size_t n;
    vector<int> sizes;



    const Solution& solution() const;
    auto solve() -> decltype(solution());
    vector<Item> getItems();

private:
    bool compare(const Item &a, const Item &b);
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






private:
    vector<Item> items_;
    size_t       capacity_;
    population_t population_;
    size_t       iterations_;
    float        mutation_rate_;
    float pc_;
    Solution     solution_;

    mutable std::default_random_engine rng;
};