#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define nMax 100

typedef struct{
  int occ;
  int riga;
  int col;
  int len;
  int vettore[nMax];
} MyStruct;

void readFromFile(int matrix[][nMax], int *r, int* c, int* vec, int* dim, const char* filename);
void printMatrix(int matrix[][nMax], const int r, const int c);
void printVec(int* vec, const int dim);
void printStruct(MyStruct* myVec, int myDim);
void fillStruct(MyStruct* myVec, int *myDim, int matrix[][nMax], int r, int c, int* vec, int dim);

int main(){
  MyStruct myVec[nMax];
  int matrix[nMax][nMax];
  int vec[nMax];
  int dim, r, c, myDim;

  readFromFile(matrix, &r, &c, vec, &dim, "input.txt");
  memset(myVec, 0, sizeof(myVec));
  fillStruct(myVec, &myDim, matrix, r, c, vec, dim);
  printStruct(myVec, myDim);
  return 0;
}

void readFromFile(int matrix[][nMax], int *r, int* c, int* vec, int* dim, const char* filename){
  FILE *input = fopen(filename, "r");

  if(input == NULL){
    printf("Hai stra cacato nei bandalonzi!");
    exit(1);
  }

  fscanf(input, "%d %d", r, c);
  for(int i = 0; i < *r; i++){
    for(int j = 0; j < *c; j++){
      fscanf(input, "%d", &matrix[i][j]);
    }
  }

  fscanf(input, "%d", dim);
  for(int i = 0; i < *dim; i++){
    fscanf(input, "%d", &vec[i]);
  }

  fclose(input);
}

void printMatrix(int matrix[][nMax], const int r, const int c){
  for(int i = 0; i < r; i++){
    for(int j = 0; j < c; j++){
      printf("%d ", matrix[i][j]);
    }
    printf("\n");
  }
}

void printVec(int* vec, const int dim){
  for(int i = 0; i < dim; i++){
    printf("%d ", vec[i]);
  }
  printf("\n");
}

void fillStruct(MyStruct* myVec, int *myDim, int matrix[][nMax], int r, int c, int* vec, int dim){
  int counter = 0;
  int index = 0;
  int occ = -1;
  int riga, col;
  for(int i = 0; i < r; i++){
    for(int j = 0; j < c; j++){
      if(matrix[i][j] == vec[counter]){
        counter++;
        if(counter == 1){
          riga = i;
          col = j;
        }
      } 
      else if(counter == dim){
        occ++;
        counter = 0;
        myVec[index].col = col;
        myVec[index].riga = riga;
        myVec[index].occ = occ;
        myVec[index].len = dim;
        for(int k = 0; k < dim; k++){
          myVec[index].vettore[k] = vec[k];
        }
        index++;
        (*myDim)++;
      } else{
        counter = 0;
      }
    }
  }
}

void printStruct(MyStruct* myVec, int myDim){
  for(int i = 0; i < myDim; i++){
    printf("{%d,%d,%d,%d,[", myVec[i].occ, myVec[i].riga, myVec[i].col, myVec[i].len);
    for(int j = 0; j < myVec[i].len; j++){
      if(j == myVec[i].len - 1){
        printf("%d", myVec[i].vettore[j]);
      } else{
        printf("%d,", myVec[i].vettore[j]);
      }
    }
    printf("]}\n");
  }
}
