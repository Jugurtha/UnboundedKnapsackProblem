//
// Created by LENOVO on 01/05/2020.
//

#ifndef UNBOUNDEDKNAPSACKPROBLEM_STOPPINGCONDITION_H
#define UNBOUNDEDKNAPSACKPROBLEM_STOPPINGCONDITION_H


class StoppingCondition {
public:
    virtual bool operator()() = 0;
};


class StoppingConditionNbrIterations : public StoppingCondition{
public:
    explicit StoppingConditionNbrIterations(const unsigned int maxNbrIterations) : MaxNbrIterations(maxNbrIterations) {nbrIterations=0;}
    bool virtual operator()(){
        nbrIterations++;
        return nbrIterations >  MaxNbrIterations;
    }

private:
    unsigned int nbrIterations;
    const unsigned int MaxNbrIterations;
};

#endif //UNBOUNDEDKNAPSACKPROBLEM_STOPPINGCONDITION_H
