#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int indice;
    int n;
    int valori[MAX];
    float nmass;
} MatrixStruct;

int leggiMatrice(int matrix[MAX][MAX], int *nRighe, int *nColonne);
void eliminaPalindrome(int matrix[MAX][MAX], int *nRighe, int *nColonne);
void eliminaColonna(int matrix[MAX][MAX], int *nRighe, int *nColonne, int index);
void stampaMatrice(int matrix[MAX][MAX], int nRighe, int nColonne);
int MassimoMatrice(int matrix[MAX][MAX], int nRighe, int nColonne);
void riordinaStruct(MatrixStruct structArray[MAX], int dim);
void stampaStruct(MatrixStruct structArray[MAX], int dim);
void salvaStructBinario(MatrixStruct structArray[MAX], int dim, const char* fileName);
void riempiStruct(MatrixStruct structArray[MAX], int matrix[MAX][MAX], int nRighe, int nColonne);

int main() {
  int matrix[MAX][MAX];
  int nRighe = 0, nColonne = 0;

  if (leggiMatrice(matrix, &nRighe, &nColonne) != 0) {
      printf("Errore nella lettura del file\n");
      return -1;
  }

  printf("Matrice originale:\n");
  stampaMatrice(matrix, nRighe, nColonne);

  eliminaPalindrome(matrix, &nRighe, &nColonne);

  printf("\nMatrice finale:\n");
  stampaMatrice(matrix, nRighe, nColonne);

  MatrixStruct structArray[MAX];
  riempiStruct(structArray, matrix, nRighe, nColonne);

  salvaStructBinario(structArray, nRighe, "output.bin");
  stampaStruct(structArray, nRighe);

  return 0;
}

int leggiMatrice(int matrix[MAX][MAX], int *nRighe, int *nColonne) {
  FILE *fptr = fopen("input.txt", "r");
  if (fptr == NULL) {
    return -1;
  }

  fscanf(fptr, "%d %d", nRighe, nColonne);
  for (int i = 0; i < *nRighe; i++) {
    for (int j = 0; j < *nColonne; j++) {
      fscanf(fptr, "%d", &matrix[i][j]);
    }
  }

  fclose(fptr);
  return 0;
}

void stampaMatrice(int matrix[MAX][MAX], int nRighe, int nColonne) {
  for (int i = 0; i < nRighe; i++) {
    for (int j = 0; j < nColonne; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

void eliminaPalindrome(int matrix[MAX][MAX], int *nRighe, int *nColonne) {
  for (int i = 0; i < *nColonne; i++) {
    int maxIndex = *nRighe - 1;
    int check = 1;
    for (int j = 0; j < *nRighe / 2; j++) {
      if (matrix[j][i] != matrix[maxIndex--][i]) {
        check = 0;
        break;
      }
    }
    if (check == 1) {
      eliminaColonna(matrix, nRighe, nColonne, i);
      i--;
    }
  }
}

void eliminaColonna(int matrix[MAX][MAX], int *nRighe, int *nColonne, int index) {
  for (int i = 0; i < *nRighe; i++) {
    for (int j = index; j < *nColonne - 1; j++) {
      matrix[i][j] = matrix[i][j + 1];
    }
  }
  (*nColonne)--;
}

void riempiStruct(MatrixStruct structArray[MAX], int matrix[MAX][MAX], int nRighe, int nColonne) {
  int massimoGlobale = MassimoMatrice(matrix, nRighe, nColonne);
  int massimoLocale;
  for(int i = 0; i < nRighe; i++){
    massimoLocale = -INT_MAX;
    structArray[i].indice = i;
    structArray[i].n = nColonne;
    for(int j = 0; j < nColonne; j++){
      structArray[i].valori[j] = matrix[i][j];
      if(matrix[i][j] > massimoLocale)
        massimoLocale = matrix[i][j];
    }
    printf("Massimo locale: %d\tMassimo Globale: %d\n\n", massimoLocale, massimoGlobale);
    structArray[i].nmass = (float)massimoLocale / (float)massimoGlobale;
  }
}

int MassimoMatrice(int matrix[MAX][MAX], int nRighe, int nColonne){
  int max = -INT_MAX;
  for(int i = 0; i < nRighe; i++){
    for(int j = 0; j < nColonne; j++){
      if(matrix[i][j] > max)
        max = matrix[i][j];
    }
  }
  return max;
}

void riordinaStruct(MatrixStruct structArray[MAX], int dim){
  for(int i = 0; i < dim - 1; i++){
    for(int j = i + 1; i < dim; j++){
      if(structArray[i].nmass > structArray[j].nmass){
        MatrixStruct temp = structArray[i];
        structArray[i] = structArray[j];
        structArray[j] = temp;
      }
    }
  }
}
  
void stampaStruct(MatrixStruct structArray[MAX], int dim){
  for(int i = 0; i < dim; i++){
    printf("{%d %d %.2f [", structArray[i].indice, structArray[i].n, structArray[i].nmass);
    for(int j = 0; j < structArray[i].n; j++){
      printf("%d", structArray[i].valori[j]);
      if(j != structArray[i].n - 1)
        printf(" ");
    }
    printf("]}\n");
  }
}

void salvaStructBinario(MatrixStruct structArray[MAX], int dim, const char* fileName){
  FILE *fptr = fopen(fileName, "wb");
  if(fptr == NULL){
    printf("errore durante la scrittura del file binario");
    return;
  }

  fwrite(structArray, sizeof(MatrixStruct), dim, fptr);
  fclose(fptr);
}
