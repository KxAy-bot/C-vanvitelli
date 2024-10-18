#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Dati due vettori inizializzati con numeri interi random da 1 a 100 calcolare il prodotto scalare, 
// ovvero la somma dei prodotti degli elementi di uguale indice.
// Caricare come allegato il solo file sorgente (.c)
// Non inserire istruzioni di input (no lettura da console).

#define DIM 15

void stampa_array(int *array, int *sArray);

int main() {
  int v1[DIM], v2[DIM], somma = 0;
  srand(time(NULL));

  for(int i = 0; i < DIM; i++){
    v1[i] = rand() % 100 + 1;
    v2[i] = rand() % 100 + 1;
    somma += v1[i] * v2[i];
  }

  stampa_array(v1, v2);
  printf("prodotto scalare: %d", somma);
  return 0;
}

void stampa_array(int *array, int *sArray){
  for(int i = 0; i < DIM; i++)
    printf("%d\t||\t%d \n", array[i], sArray[i]);
}
