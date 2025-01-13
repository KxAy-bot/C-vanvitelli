#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct{
  int position;
  char type;
  int len;
} MyStruct;

void fillStruct(MyStruct** vec, int* dim, const char* filename);
int findPosition(char* string, char* token);
char findType(char* token);
void reorderForLen(MyStruct* vec, int dim);
void reorderForPosition(MyStruct* vec, int dim);
void printStruct(MyStruct* vec, int dim);
void saveToBin(MyStruct* vec, int dim);

int main(){
  MyStruct* vec = malloc(100 * sizeof(MyStruct));

  if(vec == NULL){
    perror("Quine McCluskey is NOT alive!");
    exit(1);
  }

  int dim;

  fillStruct(&vec, &dim, "input.txt");
  reorderForLen(vec, dim);
  reorderForPosition(vec, dim);
  printStruct(vec, dim);
  saveToBin(vec, dim);
  free(vec);
  return 0;
}

void fillStruct(MyStruct** vec, int* dim, const char* filename){
  FILE *input = fopen(filename, "r");
  char line[200];

  if(input == NULL){
    perror("Quine McCluskey is alive!");
    free(*vec);
    exit(1);
  }

  int index = 0;

  while(fgets(line, 200, input) != NULL){
    char* copy = strdup(line);
    char* token = strtok(copy, " ");

    while(token != NULL){
      (*vec)[index].position = findPosition(line, token);
      (*vec)[index].len = strlen(token);
      (*vec)[index].type = findType(token);
      index++;
      token = strtok(NULL, " ");
    }
  }

  (*vec) = realloc(*vec, index * sizeof(MyStruct));

  if(*vec == NULL){
    perror("Quine McCluskey is still NOT alive!");
    exit(1);
  }

  (*dim) = index;
  fclose(input);
}

int findPosition(char* string, char* token){
  return (strstr(string, token) - string);
}

char findType(char* token){
  int len = strlen(token);
  int flagN = 0, flagL = 0;
  for(int i = 0; i < len; i++){
    if(isalpha(token[i]) && token[i]){
      flagL = 1;
    } else{
      flagN = 1;
    }
  }

  if(flagN == 1 && flagL == 1) return 'b';
  else if(flagN == 1 && flagL == 0) return 'c';
  else if(flagN == 0 && flagL == 1) return 'a';
  return 'n';
}

void reorderForLen(MyStruct* vec, int dim){
  for(int i = 0; i < dim; i++){
    for(int j = i + 1; j < dim; j++){
      if(vec[i].len > vec[j].len){
        MyStruct temp = vec[i];
        vec[i] = vec[j];
        vec[j] = temp;
      }
    }
  }
}

void reorderForPosition(MyStruct* vec, int dim){
  for(int i = 0; i < dim ; i++){
    for(int j = i + 1; j < dim; j++){
      if(vec[i].position > vec[j].position){
        MyStruct temp = vec[i];
        vec[i] = vec[j];
        vec[j] = temp;
      }
    }
  }
}

void printStruct(MyStruct* vec, int dim){
  for(int i = 0; i < dim; i++){
    printf("{%d,%c,%d}\n", vec[i].position, vec[i].type, vec[i].len);
  }
}

void saveToBin(MyStruct* vec, int dim){
  FILE *output = fopen("output.bin", "wb");

  if(output == NULL){
    perror("Quine McCluskey is alive!");
    free(vec);
    exit(1);
  }

  fwrite(vec, sizeof(MyStruct), dim, output);

  fclose(output);
}
