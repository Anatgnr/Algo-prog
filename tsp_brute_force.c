#include "tools.h"

//
//  TSP - BRUTE-FORCE
//
// -> la structure "point" est définie dans "tools.h"
// -> tsp_main peut être testé dès les 3 premières fonctions codées
//

double dist(point A, point B) {
  double dst = pow((B.x - A.x),2) + pow((B.y - A.y),2);
  double racine = sqrt(dst);
  return racine;
}

// 

double value(point *V, int n, int *P) {
  double cpt = 0.;
  for(int i = 0; i< n-1; i++)
    cpt += dist(V[P[i]],V[P[i+1]]);
  return (cpt += dist(V[P[n-1]],V[P[0]]));
}

double tsp_brute_force(point *V, int n, int *Q) {
  double tmp;
  double min = DBL_MAX;
  int *P = malloc(n*(sizeof(*P)));
  for(int i = 0; i<n; i++)
    P[i] = i;
  do
  {
    tmp = value(V,n,P);
    if(tmp<min)
    {
      min = tmp;
      memcpy(Q,P,n*sizeof(int));
    }
  }while(NextPermutation(P,n)&&P[0]==0);
  return min;
}

void inverser(int *P,int i, int j){
  int tmp;
  for(;i<=j;i++,j--)
    SWAP(P[i],P[j],tmp);
}

void MaxPermutation(int *P, int n, int k) {
    for(int i =k+1;i<n-1;i++){
        int tampon =i;
        for(int j=i+1;j<n-1;j++){
            if(P[j]>=P[tampon]) tampon =j;
        }
        int tmp = P[i];
        P[i]=P[tampon];
        P[tampon] = tmp;
    }
  return;
}

double value_opt(point *V, int n, int *P, double w) {
	double s =0;
    for(int i=0;i<n-1;i++){
        s+= dist(V[P[i]],V[P[i+1]]);
        if(s>w) return -(i+1);
    }
    s+=dist(V[P[n-1]],V[P[0]]);
    if(s>w)return -n;
      return s;
}

double tsp_brute_force_opt(point *V, int n, int *Q) {
    int* P=(int*)malloc(n*sizeof(int));
    for(int i=0;i<n;i++) P[i]=i;
    memcpy(Q,P,n*sizeof(int));
    double value_min=value(V,n,P);
    int k=0;
    while(NextPermutation(P,n) && running){
        drawTour(V,n,P);
        double val = value_opt(V,n,P,value_min);
        if(val <0){
            k= -val;
            MaxPermutation(P,n,k-1);

        }
        else if(val< value_min){
            value_min=val;
            memcpy(Q,P,n*sizeof(int));
        }
    }
    free(P);
	return value_min;
}
