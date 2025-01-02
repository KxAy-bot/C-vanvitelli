#include <stdio.h>
#include <stdlib.h>

#define nMax 100

typedef struct {
  int row;
  int values[2];
  int cols[2];
  int sums[2];
} MyStruct;

void readFromFile(int matrix[nMax][nMax], int* r, int* c, const char* filename);
void printMatrix(int matrix[nMax][nMax], const int r, const int c);
int sumCol(int matrix[nMax][nMax], const int r, const int col);
int sumRow(int matrix[nMax][nMax], const int row, const int c);
void fillStruct(MyStruct** vec, int* vecSize, int matrix[nMax][nMax], const int r, const int c);
void printStruct(MyStruct* vec, const int vecSize);

int main() {
  MyStruct* vec = NULL;
  int vecSize;
  int matrix[nMax][nMax];
  int r, c;

  readFromFile(matrix, &r, &c, "input.txt");
  fillStruct(&vec, &vecSize, matrix, r, c);

  printMatrix(matrix, r, c);
  printStruct(vec, vecSize);

  free(vec);
  return 0;
}

void readFromFile(int matrix[nMax][nMax], int* r, int* c, const char* filename) {
  FILE* input = fopen(filename, "r");

  if (input == NULL) {
    printf("Errore durante apertura del file di input\n");
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
 
void printMatrix(int matrix[nMax][nMax], const int r, const int c) {
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

int sumCol(int matrix[nMax][nMax], const int r, const int col) {
  int sum = 0;
  for (int i = 0; i < r; i++) {
    sum += matrix[i][col];
  }
  return sum;
}

int sumRow(int matrix[nMax][nMax], const int row, const int c) {
  int sum = 0;
  for (int i = 0; i < c; i++) {
    if (matrix[row][i] != -1)
      sum += matrix[row][i];
  }
  return sum;
}

void fillStruct(MyStruct** vec, int* vecSize, int matrix[nMax][nMax], const int r, const int c) {
  *vec = malloc(r * sizeof(MyStruct));
  *vecSize = 0;

  for(int i = 0; i < r; i++){
    int negIndices[2] = {-1, -1};
    int negCount = 0;
    for(int j = 0; j < c; j++){
      if(matrix[i][j] < 0 && negCount < 2){
        negIndices[negCount++] = j;
      }
    }

    if(negCount == 2){
      int target = 20;
      int currentSum = 0;

      for(int j = 0; j < c; j++){
        if(matrix[i][j] >= 0){
          currentSum += matrix[i][j];
        }
      }

      int diff = target - currentSum;
      matrix[i][negIndices[0]] = diff / 2;
      matrix[i][negIndices[1]] = diff - matrix[i][negIndices[0]];

      if(sumCol(matrix, r, negIndices[0]) > 20 || sumCol(matrix, r, negIndices[1]) > 20){
        (*vec)[*vecSize].row = i;
        (*vec)[*vecSize].values[0] = matrix[i][negIndices[0]];
        (*vec)[*vecSize].values[1] = matrix[i][negIndices[1]];
        (*vec)[*vecSize].cols[0] = negIndices[0];
        (*vec)[*vecSize].cols[1] = negIndices[1];
        (*vec)[*vecSize].sums[0] = sumRow(matrix, i, c);
        (*vec)[*vecSize].sums[1] = sumCol(matrix, r, negIndices[0]) + sumCol(matrix, r, negIndices[1]);

        (*vecSize)++;
      }
    }
  }
}

void printStruct(MyStruct* vec, const int vecSize) {
  if (vecSize == 0) {
    printf("No modifications were made.\n");
    return;
  }

  for (int i = 0; i < vecSize; i++) {
    printf("{%d, [%d, %d], [%d, %d], [%d, %d]}\n", vec[i].row, vec[i].values[0], vec[i].values[1], vec[i].cols[0], vec[i].cols[1], vec[i].sums[0], vec[i].sums[1]);
  }
}
