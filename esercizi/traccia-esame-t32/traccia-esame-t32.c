#include <stdio.h>
#include <stdlib.h>

#define nMax 100
#define val 30

typedef struct {
  int col; // indice della colonna
  int values[2]; // i 2 valori sostituiti nella colonna
  int rows[2]; // indici delle righe degli elementi sostituiti
  int sums[2]; // somme degli elementi nelle righe di rows
} MyStruct;

void readFromFile(int matrix[nMax][nMax], int* nRows, int* nCols, const char* filename);
void printMatrix(int matrix[nMax][nMax], int nRows, int nCols);
void fillStruct(MyStruct** vec, int matrix[nMax][nMax], int nRows, int nCols, int* size);
int calculateRowSum(int matrix[nMax][nMax], int nCols, int row);
void printStruct(MyStruct* vec, int size);


int main(){
  int matrix[nMax][nMax], nRows, nCols;
  MyStruct* vec = NULL;
  int size;

  readFromFile(matrix, &nRows, &nCols, "input.txt");
  printMatrix(matrix, nRows, nCols);

  printf("\n\n");

  fillStruct(&vec, matrix, nRows, nCols, &size);
  printStruct(vec, size);

  return 0;
}

void readFromFile(int matrix[nMax][nMax], int* nRows, int* nCols, const char* filename){
  FILE* input = fopen(filename, "r");

  if(!input){
    printf("Errore durante apertura del file\n");
    exit(-1);
  }

  fscanf(input, "%d %d", nRows, nCols);

  for(int i = 0; i < *nRows; i++){
    for(int j = 0; j < *nCols; j++){
      fscanf(input, "%d", &matrix[i][j]);
    }
  }

  fclose(input);
}

void printMatrix(int matrix[nMax][nMax], int nRows, int nCols){
  for(int i = 0; i < nRows; i++){
    for(int j = 0; j < nCols; j++){
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

void fillStruct(MyStruct** vec, int matrix[nMax][nMax], int nRows, int nCols, int* size){
  int count, structCount = 0; 

  for(int j = 0; j < nCols; j++){
    int values[2], rows[2], sums[2];
    count = 0;
    for(int i = 0; i < nRows && count < 2; i++){
      if(matrix[i][j] == -1){
        int rowSum = calculateRowSum(matrix, nCols, i);
        int nextValue = val - rowSum;
        matrix[i][j] = nextValue;
        values[count] = nextValue;
        rows[count] = i;
        sums[count] = rowSum + nextValue;
        count++;
      }
    }

    if(count == 2){
      structCount++;
      (*vec) = realloc(*vec, structCount * sizeof(MyStruct));
      (*vec)[structCount - 1].col = j;
      (*vec)[structCount - 1].values[0] = values[0];
      (*vec)[structCount - 1].values[1] = values[1];
      (*vec)[structCount - 1].rows[0] = rows[0];
      (*vec)[structCount - 1].rows[1] = rows[1];
      (*vec)[structCount - 1].sums[0] = sums[0];
      (*vec)[structCount - 1].sums[1] = sums[1];
    }
  }
  (*size) = structCount;
}

int calculateRowSum(int matrix[nMax][nMax], int nCols, int row){
  int sum = 0;
  for(int j = 0; j < nCols; j++){
    if(matrix[row][j] != -1)
      sum += matrix[row][j];
  }
  return sum;
}

void printStruct(MyStruct* vec, int size){
  for(int i = 0; i < size; i++){
    printf("{%d [%d, %d] [%d, %d] [%d, %d]}\n", vec[i].col, vec[i].values[0], vec[i].values[1], vec[i].rows[0], vec[i].rows[1], vec[i].sums[0], vec[i].sums[1]);
  }
}
