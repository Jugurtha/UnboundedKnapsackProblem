#include "HybridInit.h"





HybridInitKnapsackSolver::HybridInitKnapsackSolver(
        vector<Object> items,
int       capacity,
int       population_size,
int       iterations,
float		 pc,
float		 ph,
float        mutation_rate)

: items_{ std::move(items) }
, capacity_{ capacity }
, population_(population_size)
, iterations_{ iterations }
, mutation_rate_{ mutation_rate }
, pc_{ pc }
, ph_{ ph }
, solution_{ chromosome_t(n, {}), 0 }
, rng{ [] {
    const auto seed = std::random_device{}();
    return seed;
}() }
{
}

const HybridInitKnapsackSolver::Solution_g& HybridInitKnapsackSolver::solution() const
{
    return solution_;
}

auto HybridInitKnapsackSolver::solve() -> decltype(solution())
{
    int c = static_cast<int>(capacity_);

    HillClimbing hb(c, items_);
    int iterations = 5;
    vector<int> fitnesses(population_.size());
    std::vector<int> sols;
    sols.reserve(items_.size());
    sols.resize(items_.size());
    // Generate the first population
    n = 0;
    sizes.reserve(items_.size());
    sizes.resize(items_.size());
    for (size_t i = 0;i < items_.size();i++) {
        int dec = (int)round(capacity_ / (items_[i].weight) * 2) - 1;
        sizes[i] = countBits(dec);
        n += sizes[i];
    }
    solution_.chromosome.resize(n);
    generate(
            begin(population_),
            end(population_),
            [this] { return generate_chromosome(); });

    for (size_t k = 0; k < population_.size()*ph_;k++) {
        chromosome_t chromosome = population_[k];
        chromosome.reserve(n);
        chromosome.resize(n);
        int weight = 0;
        int value = 0;
        std::string str;
        int coef;
        int dec;
        int pt = 0;
        //chromosome.reserve(n);
        //chromosome.resize(n);
        for (size_t i = 0;i < items_.size();i++) {
            coef = 1;dec = 0;
            //for (int j = pt + sizes[i];j >pt;j--){
            for (int j = pt;j < pt + sizes[i];j++) {
                //str +=(char) chromosome[j];
                dec += chromosome[j] * coef;
                //std::cout << chromosome.size();
                coef *= 2;
            }
            sols[i] = dec;
            pt += sizes[i];

        }
        auto result_HillClimbing = hb.Run(iterations);
        sols = result_HillClimbing.tuple;
        int m = 0;
        for (size_t l = 0;l < sols.size();l++) {
            int d = sols[l];
            int r;

            while (d != 0) {
                r = (d % 2 == 0 ? 0 : 1); d /= 2;
                population_[k][m] = r;
                m++;
            }
            m += sizes[l];
        }
    }



    for (int i = 0; i < iterations_; ++i) {
        //std::cout << "Generation: " << i << '/' << iterations_;
        //std::cout << '\r' << std::flush;
        // Evaluate fitness values
        transform(
                population_.cbegin(), population_.cend(),
                begin(fitnesses), [&](auto&& chromosome) {
                    return evaluate(chromosome);
                });
        // Find the fittest chromosome
        auto best = max_element(begin(fitnesses), end(fitnesses));
        //std::cout << "best==" << best << "\n";
        const auto best_fitness = *best;
        //std::cout << "fitness : " << best - begin(fitnesses);
        //std::cout << "New solution found: " << best_fitness;
        //std::cout << " iteration=" << i << '\n';
        if (best_fitness > solution_.fitness) {
            solution_.fitness = best_fitness;
            solution_.chromosome = population_[best - begin(fitnesses)];
            std::cout << "New solution found: " << best_fitness;
            std::cout << " iteration=" << i << '\n';
        }
        // Start a new population with the current best chromosome
        population_t new_population = { solution_.chromosome };
        new_population.reserve(population_.size());
        const auto fitness_sum = accumulate(
                cbegin(fitnesses), cend(fitnesses), int{});
        // Generate remaining chromosomes based on selection and crossover
        float p = (rand() / RAND_MAX);
        if (p < pc_) {
            generate_n(
                    back_inserter(new_population), population_.size() - 1,
                    [&] {
                        auto chromosome_1 = select(fitnesses, fitness_sum);
                        auto chromosome_2 = select(fitnesses, fitness_sum);
                        return crossover(chromosome_1, chromosome_2);
                    });
        }

        // Mutate some of the chromosomes
        for (auto& chromosome : new_population) {
            mutate(chromosome);
        }

        // Prepare the new population for next iterations
        population_ = std::move(new_population);
    }
    return solution();
}

vector<Object> HybridInitKnapsackSolver::getItems() {
    return items_;
}



bool HybridInitKnapsackSolver::compare(const Object &a, const Object &b)
{
    return a.value / a.weight < b.value / b.weight;
}

unsigned HybridInitKnapsackSolver::countBits(unsigned int number)
{
    // log function in base 2
    // take only integer part
    return (int)log2(number) + 1;
}
void HybridInitKnapsackSolver::convertToBinary(int n)
{
    if (n / 2 != 0) {
        convertToBinary(n / 2);
    }
    printf("%d", n % 2);
}

chromosome_t HybridInitKnapsackSolver::generate_chromosome() const
{
    std::bernoulli_distribution coin_flip{ 0.0001 };

    chromosome_t chromosome;
    chromosome.reserve(n);
    int eval = 0;
    //chromosome.resize(n);

    generate_n(
            back_inserter(chromosome),
            n,
            [&] { return coin_flip(rng); });



    return chromosome;
}
int HybridInitKnapsackSolver::evaluate(const chromosome_t& chromosome) const
{
    // Get value of all items or 0 if weight exceeds capacity
    int weight = 0;
    int value = 0;
    std::string str;
    int coef;
    int dec;
    int pt = 0;
    //chromosome.reserve(n);
    //chromosome.resize(n);
    for (size_t i = 0;i < items_.size();i++) {
        coef = 1;dec = 0;
        //for (int j = pt + sizes[i];j >pt;j--){
        for (int j = pt;j < pt + sizes[i];j++) {
            //str +=(char) chromosome[j];
            dec += chromosome[j] * coef;
            //std::cout << chromosome.size();
            coef *= 2;
        }
        weight += items_[i].weight*dec;
        value += items_[i].value*dec;
        pt += sizes[i];
        if (weight > capacity_) {
            return 0;
        }
    }

    return value;
}

const chromosome_t& HybridInitKnapsackSolver::select(const vector<int>& fitnesses, int max) const
{
    // Wheel roulette, find a chromosome based on some probability value
    std::uniform_int_distribution<int> random_value{ 0, max };

    const auto it = find_if(
            cbegin(fitnesses),
            cend(fitnesses) - 1,
            [offset = int{}, pick = random_value(rng)]
                    (auto fitness) mutable {
                return pick < (offset += fitness);
            });
    return population_[it - cbegin(fitnesses)];
}

void HybridInitKnapsackSolver::mutate(chromosome_t& chromosome)
{


    // Flip random bits
    std::uniform_real_distribution<float> random_chance{};
    for (auto&& has_item : chromosome) {
        if (random_chance(rng) < mutation_rate_) {
            has_item = !has_item;
        }
    }
}

chromosome_t HybridInitKnapsackSolver::crossover(
        const chromosome_t& chromosome_1,
        const chromosome_t& chromosome_2)
{
    // Slice two chromosomes at a point and join the left side
    // ...  of the first with the right side of the second

    std::uniform_int_distribution<int> random_index{ 0, n };

    auto slice = random_index(rng);
    chromosome_t new_chromosome(n);
    //new_chromosome.reserve(n);
    //new_chromosome.resize(n);
    copy(
            begin(chromosome_2) + slice,
            end(chromosome_2),
            copy_n(
                    begin(chromosome_1),
                    slice,
                    begin(new_chromosome))
    );
    return new_chromosome;
}

int HybridInitKnapsackSolver::weight(const chromosome_t& chromosome) const
{
    // Get value of all items or 0 if weight exceeds capacity
    int weight = 0;


    for (size_t i = 0;i < items_.size();i++) {
        weight += items_[i].weight*chromosome[i];
    }
    return weight;
}

std::vector<int> HybridInitKnapsackSolver::getObjects()
{
    size_t weight = 0;
    size_t value = 0;
    int coef;
    int dec;
    int pt = 0;
    vector <Object> objs = getItems();

    std::vector<int> objects;
    for(unsigned int i =0;i<objs.size(); i++)
        objects.push_back(0);

    for (unsigned int i = 0;i <sizes.size();i++) {
        coef = 1;dec = 0;
        for (int j = pt;j < pt + sizes[i];j++) {
            dec += solution_.chromosome[j] * coef;
            coef *= 2;

        }
        weight += objs[i].weight*dec;
        value += objs[i].value*dec;
        pt += sizes[i];

        objects[i] = dec;
    }
    return objects;
}
