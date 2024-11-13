#include <stdio.h>
#include <stdlib.h>
#define nMax 100

void sortH(int matrix[nMax][nMax], int dimensione);
void sortV(int matrix[nMax][nMax], int dimensione);
void check_is_ordered(int matrix[nMax][nMax], int dimensione);

void print_matrix(int matrix[nMax][nMax], int dimensione){
  printf("{");
  for(int i = 0; i < dimensione; i++){
    for(int j = 0; j < dimensione; j++){
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
  printf("}");
}

int main() {
  int matrix[nMax][nMax], dimensione, ordine;
  printf("quanto vuoi che sia grande la matrice: ");
  scanf("%d", &dimensione);

  for(int i = 0; i < dimensione; i++){
    for(int j = 0; j < dimensione; j++){
      printf("Inserisci l-elemento a i:%d e j:%d: ", i,j);
      scanf("%d", &matrix[i][j]);
    }
  }

  print_matrix(matrix, dimensione);

  printf("\n\n In che modo vuoi riordinare la matrice? \n\n1)\tVerticale\n2)\tOrizzontale\n Scegli: ");
  scanf("%d", &ordine);

  switch(ordine){
    case 1:
      sortV(matrix, dimensione);
      printf("\n");
      print_matrix(matrix, dimensione);
      break;
    case 2:
      sortH(matrix, dimensione);
      printf("\n");
      print_matrix(matrix, dimensione);
      break;
  }

  return 0;
}

void check_is_ordered(int matrix[nMax][nMax], int dimensione){
  int is_ordered = 1;
  for(int i = 0; i < dimensione; i++){
    for(int j = 0; j < dimensione - 1;j ++){
      for(int k = 0; k < dimensione - 1; k++){
        if(matrix[i][k] > matrix[i][k + 1]){
          is_ordered = 0;
        }
      }
    }
  }
  if(is_ordered){
    printf("La matrice è ordinata\n");
  }else{
    printf("La matrice non è ordinata\n");
  }
}

void sortH(int matrix[nMax][nMax], int dimensione){
  for(int i = 0; i < dimensione; i++){
    for(int j = 0; j < dimensione - 1;j ++){
      for(int k = 0; k < dimensione - 1; k++){
        if(matrix[i][k] > matrix[i][k + 1]){
          int temp = matrix[i][k];
          matrix[i][k] = matrix[i][k + 1];
          matrix[i][k + 1] = temp;
        }
      }
    }
  }
}

void sortV(int matrix[nMax][nMax], int dimensione){
  for(int i = 0; i < dimensione; i++){
    for(int j = 0; j < dimensione - 1;j ++){
      for(int k = 0; k < dimensione - 1; k++){
        if(matrix[k][i] > matrix[k + 1][i]){
          int temp = matrix[k][i];
          matrix[k][i] = matrix[k + 1][i];
          matrix[k + 1][i] = temp;
        }
      }
    }
  }
}
