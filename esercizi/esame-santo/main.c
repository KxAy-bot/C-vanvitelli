#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nMax 100

typedef struct{
  int row[nMax]; // Vector sequence
  int n; // Size of the vector
  int i; // Row index
} MyStruct;

typedef struct{
  int key;
  int count;
} HashMap;

void readFromFile(int matrix[nMax][nMax], int *r, int *c, const char* filename);
void fillStruct(MyStruct* vec, int* dim, int matrix[nMax][nMax], int r, int c);
void getSequence(int* sequenceVec, int *rowDim, int matrix[nMax][nMax], int row, int c);
void printStruct(MyStruct* vec, int dim);
int linearSearch(HashMap* map, int key, int dim);
void addToMap(HashMap** map, int key, int* dim);
void printHashMap(HashMap* map, int dim);

int main(){
  MyStruct vec[nMax];
  int matrix[nMax][nMax];
  int r, c, dim;

  readFromFile(matrix, &r, &c, "input.txt");
  fillStruct(vec, &dim, matrix, r, c);
  printStruct(vec, dim);

  return 0;
}

void readFromFile(int matrix[nMax][nMax], int *r, int *c, const char* filename){
  FILE *input = fopen(filename, "r");

  if(input == NULL){
    printf("Error: Unable to open the file.\n");
    exit(1);
  }

  fscanf(input, "%d %d", r, c);
  for(int i = 0; i < *r; i++){
    for(int j = 0; j < *c; j++){
      fscanf(input, "%d", &matrix[i][j]);
    }
  }

  fclose(input);
}

void fillStruct(MyStruct* vec, int *dim, int matrix[nMax][nMax], int r, int c){
  int count = 0;

  for(int i = 0; i < r; i++){
    int n;
    int row[nMax];
    getSequence(row, &n, matrix, i, c);
    vec[i].i = i;
    vec[i].n = n;
    memcpy(vec[i].row, row, n * sizeof(int));
    count += 1;
  }

  (*dim) = count;
}

void getSequence(int* sequenceVec, int *rowDim, int matrix[nMax][nMax], int row, int c){
  HashMap* map = NULL;
  int dim = 0, index = 0;

  for(int i = 0; i < c; i++){
    addToMap(&map, matrix[row][i], &dim);
  }

  for(int i = 0; i < dim; i++){
    sequenceVec[index++] = map[i].key;
    sequenceVec[index++] = map[i].count;
  }

  free(map);
  (*rowDim) = index;
}

void printStruct(MyStruct* vec, int dim){
  for(int i = 0; i < dim; i++){
    printf("{%d,%d, [", vec[i].i, vec[i].n);
    for(int j = 0; j < vec[i].n; j++){
      printf("%d", vec[i].row[j]);
      if(j < vec[i].n - 1) printf(", ");
    }
    printf("]}\n");
  }
}

int linearSearch(HashMap* map, int key, int dim){
  for(int i = 0; i < dim; i++){
    if(key == map[i].key){
      map[i].count++;
      return 0;
    }
  }
  return -1;
}

void addToMap(HashMap** map, int key, int* dim){
  if(*map == NULL && *dim == 0){
    *map = malloc(sizeof(HashMap));
    (*dim)++;
    (*map)[0].key = key;
    (*map)[0].count = 1;
    return;
  }

  if(linearSearch(*map, key, *dim) == -1){
    (*dim)++;
    *map = realloc(*map, *dim * sizeof(HashMap));
    (*map)[(*dim) - 1].key = key;
    (*map)[(*dim) - 1].count = 1;
  }
}

void printHashMap(HashMap* map, int dim){
  for(int i = 0; i < dim; i++){
    printf("{%d, %d}\n", map[i].key, map[i].count);
  }
}
