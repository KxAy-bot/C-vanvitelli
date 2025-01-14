#include <stdio.h>
#include <stdlib.h>

#define nMax 100
#define copyRow 3

void readFromFile(int*** matrix, int* r, int* c, const char* filename);
void fillMatrix(int** matrix, int r, int c, int copy[][r*c]);
void reorderMatrix(int r, int c, int matrix[][r*c]);
void printMatrix(int dim, int matrix[][dim]);
void deleteCol(int* dim, int matrix[][*dim]);
void saveToBin(int dim, int matrix[][dim]);

int main(){
  int** matrix = NULL;
  int r, c;
  readFromFile(&matrix, &r, &c, "input.txt");
  int dim = r * c;
  int copy[3][dim];
  fillMatrix(matrix, r, c, copy);
  printMatrix(dim, copy);
  printf("\n");
  reorderMatrix(r, c, copy);
  deleteCol(&dim, copy);
  printMatrix(dim, copy);
  saveToBin(dim, copy);
  return 0;
}

void readFromFile(int*** matrix, int* r, int* c, const char* filename){
  FILE *input = fopen(filename, "r");

  if(input == NULL){
    perror("George Droyde sta venendo a prenderti");
    exit(1);
  }

  fscanf(input, "%d %d", r, c);

  *matrix = (int**)malloc(*r * sizeof(int*));
  for(int i = 0; i < *r; i++){
    (*matrix)[i] = malloc(*c * sizeof(int));
  }

  for(int i = 0; i < *r; i++){
    for(int j = 0; j < *c; j++){
      fscanf(input, "%d", &(*matrix)[i][j]);
    }
  }

  fclose(input);
}

void fillMatrix(int** matrix, int r, int c, int copy[][r*c]){
  int index = 0;
  for(int i = 0; i < r; i++){
    for(int j = 0; j < c; j++){
      copy[0][index] = matrix[i][j];
      copy[1][index] = i;
      copy[2][index] = j;
      index++;
    }
  }
}

void reorderMatrix(int r, int c, int matrix[][r*c]) {
  for (int j = 0; j < r*c - 1; j++) {
    for(int k = j+1; k < r*c; k++){
      if(matrix[0][j] < matrix[0][k]){
        for(int l = 0; l < 3; l++){
          int temp = matrix[l][j];
          matrix[l][j] = matrix[l][k];
          matrix[l][k] = temp;
        }
      }
    }
  }
}

void printMatrix(int dim, int matrix[][dim]){
  for(int i = 0; i < 3; i++){
    for(int j = 0; j < dim; j++){
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

void deleteCol(int* dim, int matrix[][*dim]){
  int counter = 0;
  for(int j = 0; j < *dim; j++){
    if(matrix[0][j] == 0){
      for(int k = j; k < *dim; k++){
        matrix[0][k] = matrix[0][k+1];
        matrix[1][k] = matrix[1][k+1];
        matrix[2][k] = matrix[2][k+1];
      }
      counter++;
    }
  }
  (*dim) = *dim - counter;
}

void saveToBin(int dim, int matrix[][dim]){
  FILE *output = fopen("output.bin", "wb");
  int tempDim = dim;
  int tempRow = copyRow;

  if(output == NULL){
    perror("sei negro");
    exit(1);
  }

  fwrite(&tempDim, sizeof(int), 1, output);
  fwrite(&tempRow, sizeof(int), 1, output);

  for(int i = 0; i < tempRow; i++){
    for(int j = 0; j < dim; j++){
      fwrite(&matrix[i][j], sizeof(int), tempRow*dim, output);
    }
  }
}
