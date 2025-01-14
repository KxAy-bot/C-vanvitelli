#include <stdio.h>
#include <stdlib.h>

#define nMax 100

typedef struct{
  float media;
  char letter;
  int index;
} MyStruct;

void readFromFile(int matrix[nMax][nMax], int* r, int* c, const char* filename);
void fillStruct(MyStruct* vec, int matrix[nMax][nMax], int r, int c);
float calculateAverageRows(int matrix[nMax][nMax], int row, int c);
float calculateAverageCols(int matrix[nMax][nMax], int r, int col);
void reorderStruct(MyStruct* vec, int dim);
void printStruct(MyStruct* vec, int dim);
void saveToBin(MyStruct* vec, int dim, const char* filename);

int main(){
  int matrix[nMax][nMax];
  int r, c, dim;
  readFromFile(matrix, &r, &c, "input.txt");
  dim = r + c;
  MyStruct vec[dim];
  fillStruct(vec, matrix, r, c);
  reorderStruct(vec, dim);
  printStruct(vec, dim);
  saveToBin(vec, dim, "output.bin");
  return 0; 
}

void readFromFile(int matrix[nMax][nMax], int* r, int* c, const char* filename){
  FILE *input = fopen(filename, "r");

  if(input == NULL){
    perror("Resuscitate Quine McCluskey bastardi!");
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

float calculateAverageRows(int matrix[nMax][nMax], int row, int c){
  float buffer = 0;
  for(int i = 0; i < c; i++){
    buffer += matrix[row][i];
  }
  return buffer / (float)c;
}

float calculateAverageCols(int matrix[nMax][nMax], int r, int col){
  int buffer = 0;
  for(int i = 0; i < r; i++){
    buffer += matrix[i][col];
  }
  return (float)buffer / (float)r;
}

void fillStruct(MyStruct* vec, int matrix[nMax][nMax], int r, int c){
  int index = 0;
  for(int i = 0; i < r; i++){
    vec[index].index = i;
    vec[index].media = calculateAverageRows(matrix, i, c);
    vec[index].letter = 'r';
    index++;
  }

  for(int i = 0; i < c; i++){
    vec[index].index = i;
    vec[index].media = calculateAverageCols(matrix, r, i);
    vec[index].letter = 'c';
    index++;
  }
}

void reorderStruct(MyStruct* vec, int dim){
  for(int i = 0; i < dim - 1; i++){
    for(int j = i + 1; j < dim; j++){
      if(vec[i].media > vec[j].media){
        MyStruct temp = vec[i];
        vec[i] = vec[j];
        vec[j] = temp;
      }
    }
  }
}

void printStruct(MyStruct* vec, int dim){
  for(int i = 0; i < dim; i++){
    printf("%f,%c,%d\n", vec[i].media, vec[i].letter, vec[i].index);
  }
}

void saveToBin(MyStruct* vec, int dim, const char* filename){
  FILE *output = fopen(filename, "wb");

  if(output == NULL){
    perror("Resuscitate Quine McCluskey bastardi!");
    exit(1);
  }

  fwrite(vec, sizeof(MyStruct), dim, output);

  fclose(output);
}
