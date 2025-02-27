//
// Created by LENOVO on 01/05/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_FITNESS_H
#define UNBOUNDEDKNAPSACKPROBLEM_FITNESS_H


class Fitness {
public:
    virtual double operator()(Solution solution) = 0;
};


class FitnessValue : public Fitness{
public:
    double virtual operator()(Solution solution)
    {
        return solution.value;
    }
};


#endif //UNBOUNDEDKNAPSACKPROBLEM_FITNESS_H
