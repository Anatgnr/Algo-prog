#include "heap.h"
#include "tools.h"
#include <stdlib.h>
#include <stdio.h>

heap heap_create(int k, int (*f)(const void *, const void *)) {
  heap h = malloc(sizeof(*h));
  h->nmax = k;
  h->n = 0;
  h->f = f;
  h->array = malloc((k+1) * sizeof(void *));
  return h;
}

void heap_realloc(heap h){
  h->nmax *= 2;
  h->array = realloc(h->array, h->nmax* sizeof(void *));
  h->array--;
}

void heap_destroy(heap h){
  if(h != NULL)
  {
    free(h->array);
    free(h);
    printf("Heap is destroyed");
  }
  printf("Heap is already NULL");
}

bool heap_empty(heap h) {
  return (h->n == 0);
}

bool heap_add(heap h, void *object) {
  // cas d'erreur
  if(h->n > h->nmax || h->n < 0)   
    return true;
  //si plus de place dans le tableau
  if(h->nmax == h->n)
    heap_realloc(h);
  //insertion en bas du tas
  h->n++;
  int cursor = h->n;
  h->array[cursor] = object;
  //test si on doit trier
  if(cursor == 1)
    return false;
  void * tmp;
  //tri
  while(h->f(h->array[cursor], h->array[cursor/2]) < 0)
    {
      SWAP(h->array[cursor], h->array[cursor/2],tmp);
      cursor /= 2;
      if(cursor <= 1)
        break;
    }
  return false;
}

void *heap_top(heap h) {
  if(heap_empty(h) || h->array[1] == NULL){return NULL;}
  return h->array[1];
}

void *heap_pop(heap h){
  if(heap_empty(h)){return NULL;}// le tas est vide pas de suppression

  void * save = h->array[1];
  //swap de la valeur a supprimer avec la derniere feuille
  void* tmp;
  SWAP(h->array[1],h->array[h->n],tmp);
  //reajustement des variables de stockage
  h->n --; 
  //reequilibrage du tas
  int cursor = 1;
  //tant qu'on a pas un tas binaire
  while(true)
  {
    int gauche = cursor * 2;
    int droit = cursor * 2 + 1;
    // Cas deux fils gauche et
    if(cursor * 2 + 1 <= h->n)
    {
      //si gauche plus petit que droit
      // f effectue b - a
      if(h->f(h->array[gauche], h->array[droit]) < 0)
        //si curseur plus petit que gauche
        if(h->f(h->array[cursor], h->array[gauche]) > 0)
        {
          //swap curseur a gauche
          SWAP(h->array[cursor], h->array[gauche],tmp);
          cursor *= 2;
          printf("swap Gauche\n");
        }    
      //si droit plus petit que gauche
      if(h->f(h->array[gauche], h->array[droit]) >= 0)
        //si curseur plus petit que droit
        if(h->f(h->array[cursor], h->array[droit]) > 0)
        {
          //swap curseur a droit
          SWAP(h->array[cursor], h->array[droit],tmp);
          cursor = 2* cursor +1;
          printf("swap Droit\n");
        }     
    } 
    //1 seul fils donc forcément fils gauche
    else if(cursor * 2 <= h->n && h->f(h->array[cursor], h->array[gauche]) > 0)
    {
      SWAP(h->array[cursor], h->array[gauche],tmp);
      cursor *= 2;
      printf("swap Droit\n");
    }  
    //si tout est bon on quitte la boucle
    else
      break;
  }
  return save;
}
