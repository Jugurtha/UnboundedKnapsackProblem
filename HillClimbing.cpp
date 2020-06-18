
#include "HillClimbing.h"
using std::vector;

HillClimbing::HillClimbing(unsigned int maxWeight, Objects objects)//:maxWeight(maxWeight)
{
    for(auto object : objects)
    {
        weights.push_back(object.weight);
        values.push_back(object.value);
    }
      this->maxWeight =maxWeight;
   // this->rounds = rounds;
    //this->iterations = iterations;
}

vector<int> HillClimbing::Initial_solution()
{
    vector<int> solution(weights.size());
    int i=0,rd=0;
    int poids=0,poids_temp=0;
    for ( i = 0; i < weights.size(); i ++){solution[i]=0;}
    for ( i = 0; i < weights.size(); i ++){
        rd=rand()%weights.size();
        poids_temp=poids+weights[i]*rd;
        if (poids_temp<=maxWeight)
        {
            solution[i] = rd;
            poids=poids+weights[i]*solution[i];
        }
    }
    return solution ;
};

vector<int> HillClimbing::Ajout(vector<int> &solution, int indice){

    int weight_cpt=0,values_T=0;
	int i=0;

    for (i = 0; i < weights.size(); i++) {
        weight_cpt = weights[i]*solution[i] + weight_cpt;
        values_T = values_T + values[i]*solution[i];
    }
    weight_cpt = weight_cpt + weights[indice];
    values_T = values_T + values[indice];
    if (weight_cpt <= maxWeight)
    {
        solution[indice] = solution[indice] + 1;
    }

        // std::cout << "weight : " << weight <<"\n";

    return solution;
};

int HillClimbing::Evaluation(vector<int> &solution)
{
    int value = 0;
	int i=0;
    for( i = 0; i < solution.size(); i++)
    {
        if(solution[i] > 0)
        {
            value += values[i]*solution[i];
        }
    }
    return value;
};

Solution HillClimbing::Determination(Solution candidata, Solution global){
    if(candidata.value > global.value)
    {
        global.tuple = candidata.tuple;
        global.value = candidata.value;
    }
    return global;
};

void HillClimbing::print_solution(Solution candidata)
{   int i=0;
    for ( i = 0 ;i < weights.size() ; i ++)
    {
        std::cout << candidata.tuple[i] << " ";
    }
    std::cout << "\n";
    std::cout << candidata.value << "\n";
};

Solution HillClimbing::Run(Solution optimale,int rounds)
{
    int round = 0;
Solution global,candidata,global_save;
    global.tuple = Initial_solution();
    global.value = Evaluation(global.tuple);
    global_save.tuple=global.tuple;
    global_save.value= global.value;
    int max=global.value,save_i=0,booleen=1;
    while((booleen==1)&&(round<rounds))
    {
        booleen=0;
        // std::cout << "round : " << round << "\n";
   candidata.tuple = global.tuple;
        candidata.value = Evaluation(candidata.tuple);
candidata.tuple[(round % values.size())]--;
candidata.value=candidata.value-values[round];
        global.tuple = candidata.tuple;
        global.value = Evaluation(global.tuple);

        for (int i = 0; i < weights.size() ; i ++){
            candidata.tuple = Ajout(global.tuple,i);
            global.tuple=global_save.tuple;
            candidata.value = Evaluation(candidata.tuple);
            if (max<candidata.value) {
                booleen=1;
                max=candidata.value;
                save_i = i;
            }
            if(candidata.tuple == optimale.tuple)
            {
                return candidata;
            }
        }
        if (booleen==1) {
            global.tuple = Ajout(global.tuple, save_i);
            global.value = Evaluation(global.tuple);
            global = Determination(global_save,global);
            global_save.tuple = global.tuple;
            global_save.value = global.value;
        }
        ++round;
    }
	       // print_solution(global);
return global;
};
