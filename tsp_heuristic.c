#include "tools.h"
#include "tsp_brute_force.h"

//
//  TSP - HEURISTIQUES
//

void reverse(int *T, int p, int q) {
  // Renverse la partie T[p]...T[q] du tableau T avec p<q si
  // T={0,1,2,3,4,5,6} et p=2 et q=5, alors le nouveau tableau T sera
  // {0,1, 5,4,3,2, 6}.
  int tmp;
  for(;p<q;p++,q--) {
    SWAP(T[p],T[q],tmp);
  return;
  }
}

double first_flip(point *V, int n, int *P) {
  // Renvoie le gain>0 du premier flip réalisable, tout en réalisant
  // le flip, et 0 s'il n'y en a pas.
  //cas avec i = 0 et j = n-1 pour le premier flip de la tournée
  double gain = 0.0;
  for (int i = 0; i < n-2; i++)  
    for(int j = i+2;  j< n; j++)
  {
    double avant = dist(V[P[i]], V[P[i+1]]) + dist(V[P[j]], V[P[(j+1)%n]]);
    double apres = dist(V[P[i]], V[P[j]]) + dist(V[P[i+1]], V[P[(j+1)%n]]);
    if (apres < avant)
    {
      reverse(P, i+1, j);
      gain = avant - apres;
    }
  }
  return gain;
}

double tsp_flip(point *V, int n, int *P) {
  // La fonction doit renvoyer la valeur de la tournée obtenue. Pensez
  // à initialiser P, par exemple à P[i]=i. Pensez aussi faire
  // drawTour() pour visualiser chaque flip.
  double d=0;
  for(int i=0;i<n;i++){
    P[i]=i;
    d+=dist(V[P[(i-1)%n]],V[P[i]]);
  }
  double gain;
  while ((gain=first_flip(V,n,P))!=0)
  {
    d-=gain;
    drawTour(V,n,P);
  }
  return d;
}

double tsp_greedy(point *V, int n, int *P) {
  // La fonction doit renvoyer la valeur de la tournée obtenue. Pensez
  // à initialiser P, par exemple à P[i]=i.
  ;
  ;
  ;
  return 0.0;
}
