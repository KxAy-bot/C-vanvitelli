#include <stdio.h>

#define DIM 100

void print_array(int *array);
void shift_array(int *array, int index, int n);
void remove_element(int *array, int index);

int main() {
  int n, index = 0;
  int array[DIM] = {1, 2, 3, 4,5,6,7,8,9,10};
  printf("Inserisci il numero: \n");
  scanf("%d", &n);
  printf("Inserisci a che index inserirlo: \n");
  scanf("%d", &index);

  shift_array(array, index, n);
  print_array(array);

  printf("\nInserisci l'index da rimuovere: \n");
  scanf("%d", &index);
  remove_element(array, index);

  print_array(array);
}

void print_array(int *array){
  for(int i = 0; i < DIM; i++)
    printf("%d ", array[i]);
}

void shift_array(int *array, int index, int n){
  for(int i = DIM-1; i > index; i--)
    array[i] = array[i-1];
  array[index] = n;
}

void remove_element(int *array, int index){
  for(int i = index; i < DIM-1; i++)
    array[i] = array[i+1];
}
