#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define nMax 100

typedef struct{
  char* parola;
  int index;
} MyStruct;

void readFromFile(int matrix[nMax][nMax], int* r, int *c, const char* filename);
void convertToString(int matrix[nMax][nMax], int r, int c, char string[nMax], int* len);
void fillStruct(MyStruct** vec, int* vecDim, char stringa[nMax], int len);
void printStruct(MyStruct* vec, int vecDim);
void saveToBin(MyStruct* vec, int vecDim);

int main(){
  MyStruct* vec = malloc(nMax * sizeof(MyStruct));
  int matrix[nMax][nMax];
  char stringa[nMax];
  int r, c, len, vecDim;

  readFromFile(matrix, &r, &c, "input.txt");
  convertToString(matrix, r, c, stringa, &len);
  fillStruct(&vec, &vecDim, stringa, len);
  printStruct(vec, vecDim);
  saveToBin(vec, vecDim);

  free(vec);
  return 0;
}

void readFromFile(int matrix[nMax][nMax], int* r, int *c, const char* filename){
  FILE *input = fopen(filename, "r");

  if(input == NULL){
    perror("QUINE MCLUSKEY IS STILL ALIVE!");
  }

  fscanf(input, "%d %d", r, c);
  for(int i = 0; i < *r; i++){
    for(int j = 0; j < *c; j++){
      fscanf(input, "%d", &matrix[i][j]);
    }
  }

  fclose(input);
}

void convertToString(int matrix[nMax][nMax], int r, int c, char string[nMax], int* len){
  for(int i = 0; i < r; i++){
    for(int j = 1; j < c; j++){
      if(matrix[i][j] != -1){
        string[matrix[i][j]] = (char)matrix[i][0];
        (*len)++;
      }
    }
  }
  string[*len] = '\0';
}

void fillStruct(MyStruct** vec, int* vecDim, char stringa[nMax], int len){
  char* copy = strdup(stringa);

  if(copy == NULL){
    perror("Dioporco");
    exit(1);
  }

  char* token = strtok(copy, " ");

  int index = 0;

  while(token != NULL){
    (*vec)[index].index = (int)(strstr(stringa, token) - stringa);
    (*vec)[index].parola = malloc((strlen(token) + 1) * sizeof(char));
    strcpy((*vec)[index].parola, token);
    index++;
    token = strtok(NULL, " ");
  }

  (*vecDim) = index;
  (*vec) = realloc(*vec, index * sizeof(MyStruct));

  free(copy);
}

void printStruct(MyStruct* vec, int vecDim){
  for(int i = 0; i < vecDim; i++){
    printf("%s, %d\n", vec[i].parola, vec[i].index);
  }
}

void saveToBin(MyStruct* vec, int vecDim){
  FILE *output = fopen("output.bin", "wb");

  if(output == NULL){
    perror("Sei negro");
    exit(1);
  }

  fwrite(vec, sizeof(MyStruct), vecDim, output);

  fclose(output);
}
