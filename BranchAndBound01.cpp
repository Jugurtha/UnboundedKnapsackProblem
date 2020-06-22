//
// Created by LENOVO on 21/06/2020.
//

#include "BranchAndBound01.h"

BranchAndBound01::BranchAndBound01(int maxWeight, Object obj[], int nbr)
{
    W = maxWeight;
    n = nbr;
    for(int i = 0; i<nbr; i++)
    {
        arr[i].value = obj[i].value;
        arr[i].weight = obj[i].value;
    }
}

// fonction de comparaison permettant d'ordonner les objets selon le ration valeur/poids
bool BranchAndBound01::cmp(Object a, Object b)
{
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}


// La fonction majorant retourne la limite du profit dans le sous-arbre ayant pour racine u
//la fonction utilisera la méthode de la solution gloutonne pour majorer la solution optimale

int BranchAndBound01::bound(Noeud u, int n, int W, Object arr[])
{
    // si le poids dépasse la capacité du sac on retourne 0 comme majorant
    if (u.poid >= W)
        return 0;

    // initialiser la limite par le profit courant
    int majorant = u.profit;

    // on commence à rajouter les objets ayant pour index dans arr niveau du noeud u +1
    int j = u.niveau + 1;
    int poidcourant = u.poid;
    while ((j < n) && (poidcourant + arr[j].weight <= W))
    {
        poidcourant += arr[j].weight;
        majorant += arr[j].value;
        j++;
    }
    //si j n'est pas n, on inclut le dernier objet partiellement
    //pour obtenir le majorant
    if (j < n)
        majorant += (W - poidcourant) * arr[j].value /
                    arr[j].weight;

    return majorant;
}

// retourne le profit max  qu'on peut obtenir avec une capacité W
int BranchAndBound01::knapsack()
{
    int maxProfit = 0;
    // ordonner les objets selon la valeur par unité de poids
    std::sort(arr, arr + n, [](const Object & a, const Object & b) -> bool{
        double dav = a.value, daw = a.weight;
        double dbv = b.value, dbw = b.weight;
        return (dav/daw) > (dbv/dbw);

    });

    // créer une queue pour traverser le noeud
    std::queue<Noeud> Q;
    Noeud u, v;
    u.niveau = -1;
    u.profit = u.poid = 0;
    Q.push(u);

    // un à un on extrait les objets de l'arbre de décision et on calcule
    // le profit de tous ses fils tout en continuant à enregistrer le profit max

    while (!Q.empty())
    {
        // défiler un noeud
        u = Q.front();
        Q.pop();

        // si c'est la racine on lui attribue le niveau 0
        if (u.niveau == -1)
            v.niveau = 0;

        // si il n'y a rien dans le niveau prochain continuer
        if (u.niveau == n-1)
            continue;

        // Sinon : si ce n'est pas le dernier niveau, alos on incrémente le niveau
        // et on calcule le profit des noeuds fils
        v.niveau = u.niveau + 1;
        v.poid = u.poid + arr[v.niveau].weight;
        v.profit = u.profit + arr[v.niveau].value;

        // Si le poids cumulé est inférieur à la capacité du sac : W
        // et le profit acumulé > profit max  alors on met à jour le profit max
        if (v.poid <= W && v.profit > maxProfit)
            maxProfit = v.profit;

        // obtenir le majorant  pour décider si on ajoute v à la queue Q ou pas
        v.majorant = bound(v, n, W, arr);
        if (v.majorant > maxProfit)
            Q.push(v);
        //refaire la même chose sans prendre l'objet dans le sac
        v.poid = u.poid;
        v.profit = u.profit;
        v.majorant = bound(v, n, W, arr);
        if (v.majorant > maxProfit)
            Q.push(v);
    }
    Profit = maxProfit;
    std::cout << "dynamique" <<maxProfit<< std::endl;
    return maxProfit;
}
