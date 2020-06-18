
#include "Greedy.h"

using namespace std;
/////////////////////////////////////////0-1 Knapsack ////////////////////////////////////////
Solution Greedy_Knapsack_Profit(int **item,  int n, int max) {
 //   fstream  outfile;
    Solution s;
 //   outfile.open("ResultatProfit.csv", ios::out | ios::in);
    int nbr = 0;
    int tmp = max;
    int an = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (item[i][0] < item[j][0]) swap(item[i], item[j]);
        }
    }



    for (int i = 0; i < n; i++) {
        if (tmp - item[i][1] >= 0) {
            tmp -= item[i][1];
            an += item[i][0];
            nbr++;
//            outfile << " objet numero : " << i<<" profit "<< item[i][0]<<" poids "<< item[i][1]<<endl;

            s.tuple.push_back(1);

        }
        else {

            s.tuple.push_back(0);
        }
    }


//    cout << "Greedy_Knapsack_Profit profit :" ;
//    cout << "Profit : ";
//    cout << an ;
//    cout << " poids :";
    int pod = max - tmp;
//    cout << pod << endl;

//    outfile << "nombre d'elements choisie  " << nbr << " profit Total " << an << " poids Total " << pod << endl;
//    outfile << "poids maximale   " << max << "  taille " << n+1 << endl;
//    outfile.close();
    s.value = an;
    return s;
}
////////////////////////////////////////////Unbounded Knapascak Profit.////////////////////////////////////////////
Solution Greedy_Unbounded_Knapsack_Profit(int **item,  int n, int max) {
//    fstream  outfile;
    Solution s;
//    outfile.open("ResultatProfitUbounded.csv", ios::out | ios::in);
    int nbr = 0;
    int tmp = max;
    int an = 0;
    int nbr_inst = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (item[i][0] < item[j][0]) swap(item[i], item[j]);
        }
    }
    for (int i = 0; i < n; i++) {
        if (tmp - item[i][1] >= 0) {
            nbr_inst = (tmp / item[i][1]);

            tmp -= item[i][1]* nbr_inst;
            an += item[i][0]* nbr_inst;
            nbr += nbr_inst;

 //           outfile << "objet numero : " << i << " profit " << item[i][0] << " poids " << item[i][1] <<" nbr_exemplaire   " << nbr_inst <<endl;

            s.tuple.push_back(nbr_inst);
        }
        else {

            s.tuple.push_back(0);
        }



    }

//    cout << "Greedy_Unbounded_Knapsack_Profit ";
//    cout << "Profit : ";
//    cout << an ;
//    cout << "Poids " ;
    int pod = max - tmp;
//    cout << pod << endl;

//    outfile << "nombre d'elements choisie  " << nbr << " profit Total " << an << " poids Total " << pod << endl;
//    outfile << "poids maximale   " << max << "   taille " << n+1 << endl;
//    outfile.close();
    s.value = an;
    return s;

}
////////////////////0-1 knapsack/////////////////////////////////////////////////////////////////////////
Solution Greedy_Knapsack_Weight(int **item,  int n, int max) {
 //   fstream  outfile;
    Solution s;
//    outfile.open("ResultatWight.csv", ios::out | ios::in);
    int nbr = 0;
    int tmp = max;
    int an = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (item[i][1] > item[j][1]) swap(item[i], item[j]);
        }
    }

    for (int i = 0; i < n; i++) {
        if (tmp - item[i][1] >= 0) {
            tmp -= item[i][1];
            an += item[i][0];
            nbr++;
  //          outfile << "objet numero : " << i << " profit " << item[i][0] << " poids " << item[i][1] << endl;

            s.tuple.push_back(1);
        }

        else {

            s.tuple.push_back(0);
        }
    }


//    cout << "Greedy_Knapsack_Weight profit :" ;
//    cout << "Le Profit :";
//    cout << an ;
//    cout << "Poids : " ;
    int pod = max - tmp;
 //   cout << pod << endl;
//
//    outfile << "nombre d'elements choisie  " << nbr << " profit Total " << an << " poids Total " << pod << endl;
//    outfile << "poids maximale   " << max << "  taille " << n+1 << endl;
//    outfile.close();
    s.value = an;
    return s;
}
//////////////////////////////////Knapsack Unbounded//////////////////////////////////////////////
Solution Greedy_Knapsack_Unbounded_Weight(int **item,  int n, int max) {
 //   fstream  outfile;
    Solution s;
 //   outfile.open("ResultatUnboundedWeight.csv", ios::out | ios::in);
    int nbr = 0;

    int tmp = max;
    int an = 0;
    int nbr_inst = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (item[i][1] > item[j][1]) swap(item[i], item[j]);
        }
    }

    for (int i = 0; i < n; i++) {
        if (tmp - item[i][1] >= 0) {
            nbr_inst = (tmp / item[i][1]);
            tmp -= item[i][1]* nbr_inst;
            an += item[i][0]* nbr_inst;
            nbr += nbr_inst;
 //           outfile << "objet numero : " << i << " profit " << item[i][0] << " poids " << item[i][1] << " nbr_exemplaire  " << nbr_inst << endl;

            s.tuple.push_back(nbr_inst);
        }
        else {

            s.tuple.push_back(0);
        }
    }

//    cout << "Greedy_Unbounded_Knapsack_Weight " ;
//    cout << "Profit : ";
//    cout << an ;
//    cout << "Poids : " ;
    int pod = max - tmp;
 //   cout << pod << endl;
//    outfile << "nombre d'elements choisie  " << nbr << " profit Total " << an << " poids Total " << pod << endl;
//    outfile << "poids maximale   " << max << "   taille " << n+1 << endl;
//    outfile.close();
    s.value = an;
    return s;



}
///////////////////////////////////////////Knapsack 0-1/////////////////////////////////////////////////
Solution Greedy_Knapsack_Density(int **item,  int n, int max) {
 //   fstream  outfile;
    Solution s;

 //   outfile.open("ResultatDensity.csv", ios::out | ios::in);
    int nbr = 0;

    int tmp = max;
    int an = 0;

    double arr[10000];

    for (int i = 0; i < n; i++) {
        arr[i] = (double) item[i][0] / (double)item[i][1];

    }

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (arr[i] > arr[j]) swap(item[i], item[j]);
        }
    }


    for (int i = 0; i < n; i++) {
        if (tmp - item[i][1] >= 0) {
            tmp -= item[i][1];
            an += item[i][0];
            nbr++;
  //          outfile << "objet numero : " << i << " profit " << item[i][0] << " poids " << item[i][1] << endl;

            s.tuple.push_back(1);

        }
        else {

            s.tuple.push_back(0);

        }
    }

//    cout << "Greedy_Knapsack_Density :  " ;
//    cout << "Profit :  ";
//    cout << an ;
//    cout << "Poids : " ;
    int pod = max - tmp;
//    cout << pod << endl;
//    outfile << "nombre d'elements choisie  " << nbr << " profit Total " << an << " poids Total " << pod << endl;
//    outfile << "poids maximale   " << max << "    taille   " << n+1 << endl;
//    outfile.close();
    s.value = an;
    return s;



}
///////////////////////////////Unbounded Knapsack/////////////////////////////////////////////////
Solution Greedy_Unbounded_Knapsack_Density(int **item,  int n, int max) {
//    fstream  outfile;
 //   outfile.open("ResultatUnboundedDensity.csv", ios::out | ios::in);
    int nbr = 0;
    Solution s;
    int tmp = max;
    int an = 0;
    int nbr_inst = 0;

    double arr[10000];

    for (int i = 0; i < n; i++) {
        arr[i] = (double) item[i][0] / (double) item[i][1];
    }

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (arr[i] > arr[j]) swap(item[i], item[j]);
        }
    }

    for (int i = 0; i < n; i++) {
        if (tmp - item[i][1] >= 0) {
            nbr_inst = (tmp / item[i][1]);

            tmp -= item[i][1]* nbr_inst;
            an += item[i][0]* nbr_inst;
            nbr += nbr_inst;
 //           outfile << "objet numero : " << i << " profit " << item[i][0] << " poids " << item[i][1] << " nbr_exemplaire : " << nbr_inst << endl;

            s.tuple.push_back(nbr_inst);
        }
        else {

            s.tuple.push_back(0);
        }
    }

//    cout << "Greedy_Unbounded_Knapsack_Density :" ;
//    cout << "Profit :";
//    cout << an ;
//    cout << "Poids : " ;
    int pod = max - tmp;
//    cout << pod << endl;
//    outfile << "nombre d'elements choisie  " << nbr << " profit Total " << an << " poids Total " << pod << endl;
//    outfile << "poids maximale   " << max << "   taille " << n+1 << endl;
//    outfile.close();
    s.value = an;
    return s;

}
