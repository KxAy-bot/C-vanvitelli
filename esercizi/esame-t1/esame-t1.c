#include <stdio.h>
#include <stdlib.h>

#define nMax 100

typedef struct {
  int rig;
  int c;
  int elementi[nMax];
} MyStruct;

void readFromFile(int matrix[nMax][nMax], int *r, int *c, char *filename);
void printStruct(MyStruct *vec, int r);
void printMatrix(int matrix[nMax][nMax], int r, int c);
int sumRowMatrix(int matrix[nMax][nMax], int r, int c, int row);
void fillMyStruct(MyStruct **vec, int matrix[nMax][nMax], int *r, int *c);
void orderMatrix(int matrix[nMax][nMax], int r, int c);
void swapRows(int matrix[nMax][nMax], int r, int c, int row1, int row2);
void deleteRow(int matrix[nMax][nMax], int *r, int *c, int row);
void checkSum(int matrix[nMax][nMax], int *r, int *c);

int main() {
  MyStruct *vec = NULL;
  int matrix[nMax][nMax];
  int r, c;

  readFromFile(matrix, &r, &c, "input.txt");
  orderMatrix(matrix, r, c);
  fillMyStruct(&vec, matrix, &r, &c);
  printStruct(vec, r);

  free(vec);
  return 0;
}

void readFromFile(int matrix[nMax][nMax], int *r, int *c, char *filename) {
  FILE *input = fopen(filename, "r");

  if (!input) {
    printf("Errore nell'apertura del file\n");
    exit(1);
  }

  fscanf(input, "%d %d", r, c);

  for (int i = 0; i < *r; i++) {
    for (int j = 0; j < *c; j++) {
      fscanf(input, "%d", &matrix[i][j]);
    }
  }

  fclose(input);
}

void printMatrix(int matrix[nMax][nMax], int r, int c) {
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

int sumRowMatrix(int matrix[nMax][nMax], int r, int c, int row) {
  int sum = 0;
  for (int i = 0; i < c; i++) {
    sum += matrix[row][i];
  }
  return sum;
}

void fillMyStruct(MyStruct **vec, int matrix[nMax][nMax], int *r, int *c){
  if(*vec == NULL){
    *vec = malloc(*r * sizeof(MyStruct));
  }
  int index = 0;

  checkSum(matrix, r, c);

  for(int i = 0; i < *r; i++){
    (*vec)[index].rig = i;
    (*vec)[index].c = *c;
    for(int j = 0; j < *c; j++){
      (*vec)[index].elementi[j] = matrix[i][j];
    }
    index++;
  }
}

void swapRows(int matrix[nMax][nMax], int r, int c, int row1, int row2) {
  int temp;
  for (int i = 0; i < c; i++) {
    temp = matrix[row1][i];
    matrix[row1][i] = matrix[row2][i];
    matrix[row2][i] = temp;
  }
}

void orderMatrix(int matrix[nMax][nMax], int r, int c) {
  for (int i = 0; i < r; i++) {
    for (int j = i + 1; j < r; j++) {
      if (sumRowMatrix(matrix, r, c, j) > sumRowMatrix(matrix, r, c, i)) {
        swapRows(matrix, r, c, j, i);
      }
    }
  }
}

void deleteRow(int matrix[nMax][nMax], int *r, int *c, int row){
  for (int i = row; i < *r - 1; i++){
    for (int j = 0; j < *c; j++){
      matrix[i][j] = matrix[i + 1][j];
    }
  }
  *r = *r - 1;
}

void checkSum(int matrix[nMax][nMax], int *r, int *c){
  for(int i = 0; i < *r; i++){
    int sum = sumRowMatrix(matrix, *r, *c, i);
    if(sum % 2 != 0){
      deleteRow(matrix, r, c, i);
    }
  }
}

void printStruct(MyStruct *vec, int r){
  for(int i = 0; i < r; i++){
    printf("{%d,%d,[", vec[i].rig, vec[i].c);
    for(int j = 0; j < vec[i].c; j++){
      if(j == vec[i].c - 1){
        printf("%d", vec[i].elementi[j]);
      } else{
        printf("%d,", vec[i].elementi[j]);
      }
    }
    printf("]}\n");
  }
}
