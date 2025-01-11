#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nMax 200

typedef struct{
  int linea;
  int token;
  char str[nMax];
  int value;
} MyStruct;

void fillStruct(MyStruct** vec, int* dim, const char* filename);
void allocateStruct(MyStruct** vec, int counter);
int findValue(char* string);
void printStruct(MyStruct* vec, int dim);
void orderStruct(MyStruct* vec, int dim);
void saveToBin(MyStruct* vec, int dim);
void readFromBin(MyStruct** vec, int* dim, const char* filename);

int main(){
  MyStruct* vec = malloc(sizeof(MyStruct));
  int dim;

  fillStruct(&vec, &dim, "input.txt");
  orderStruct(vec, dim);
  printStruct(vec, dim);
  saveToBin(vec, dim);
  free(vec);
  return 0;
}

void fillStruct(MyStruct** vec, int* dim, const char* filename){
  FILE *input = fopen(filename, "r");

  if(input == NULL){
    printf("Sei un richione bastardo");
    exit(1);
  }

  char line[nMax];
  int linea = 0;
  int index = 0;

  while(fgets(line, nMax, input) != NULL){
    char* copy = strdup(line);
    char* token = strtok(copy, " ,");

    int tokenCounter = 0;

    while(token != NULL){
      index++;
      tokenCounter++;
      allocateStruct(vec, index);
      (*vec)[index-1].linea = linea;
      (*vec)[index-1].token = tokenCounter;
      strcpy((*vec)[index-1].str, token);
      (*vec)[index-1].value = findValue(token);
      token = strtok(NULL, " ,");
    }

    linea++;
    free(copy);
  }
  (*dim) = index;

  fclose(input);
}

int findValue(char* string){
  int len = strlen(string);
  for(int i = 0; i < len; i++){
    if(isalpha(string[i])){
      return -1;
    }
  }
  return atoi(string);
}

void allocateStruct(MyStruct** vec, int counter){
  *vec = realloc(*vec, counter * sizeof(MyStruct));

  if(*vec == NULL){
    printf("Errore negro");
    free(vec);
    exit(1);
  }
}

void printStruct(MyStruct* vec, int dim){
  for(int i = 0; i < dim; i++){
    printf("{%d %d %s %d}\n", vec[i].linea, vec[i].token, vec[i].str, vec[i].value);
  }
}

void orderStruct(MyStruct* vec, int dim){
  int index = 0;
  for(int i = 0; i < dim - 1;i++){
    for(int j = i + 1; j < dim; j++){
      if(vec[i].value < vec[j].value){
        MyStruct temp = vec[i];
        vec[i] = vec[j];
        vec[j] = temp;
        index = i;
      }
    }
  }

  for(int i = index; i < dim - 1; i++){
    for(int j = i + 1; j < dim; j++){
      if(strcmp(vec[i].str, vec[j].str) < 0){
        MyStruct temp = vec[i];
        vec[i] = vec[j];
        vec[j] = temp;
      }
    }
  }
}

void saveToBin(MyStruct* vec, int dim){
  FILE *output = fopen("output.bin", "wb");
  
  if(output == NULL){
    printf("Hai sborrato nel puzzo");
    exit(1);
  }

  fwrite(vec, sizeof(MyStruct), dim, output);

  fclose(output);
}

void readFromBin(MyStruct** vec, int* dim, const char* filename) {
  FILE* input = fopen(filename, "rb");
  if (input == NULL) {
    printf("Errore: impossibile aprire il file binario per la lettura.\n");
    exit(1);
  }

  fseek(input, 0, SEEK_END);
  long fileSize = ftell(input);
  rewind(input);

  *dim = fileSize / sizeof(MyStruct);
  *vec = malloc(fileSize);
  if (*vec == NULL) {
    printf("Errore: memoria insufficiente per leggere il file binario.\n");
    fclose(input);
    exit(1);
  }

  fread(*vec, sizeof(MyStruct), *dim, input);

  fclose(input);
}
