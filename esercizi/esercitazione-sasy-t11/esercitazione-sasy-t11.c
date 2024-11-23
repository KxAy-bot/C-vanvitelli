#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nMax 100

typedef struct{
  char line[nMax]; // linea del testo da dividere
  int n; // numero di token trovati
  int tokens[nMax][2]; // per ogni token trovato, contiene il primo e l-ultimo indice della lettera del token nella stringa
  char dels[nMax]; // contiene i soli delimitatori trovati nella stringa, presi una sola volta
} MyStruct;

void fillStruct(MyStruct** vec, int* size, const char* filename);
void findDel(char* line, char* del, char* dels);
void findIndex(char* line, char* token, int tokens[nMax][2], int n);
void printStruct(MyStruct* vec, int size);

int main(){
  MyStruct* vec = NULL;
  int size;

  fillStruct(&vec, &size, "input.txt");
  printStruct(vec, size);

  free(vec);
  return 0; 
}

void fillStruct(MyStruct** vec, int* size, const char* filename){
  FILE *input = fopen(filename, "r");
  char line[nMax];
  char del[nMax];
  char dels[nMax];
  int count = 0, n;

  if(!input){
    printf("Errore nell'apertura del file %s\n", filename);
    exit(-1);
  }

  strcpy(del, fgets(line, sizeof(line), input));

  if(del[strlen(del)-1] == '\n')
    del[strlen(del)-1] = '\0';

  while(fgets(line, sizeof(line), input)){
    count++;
    *vec = realloc(*vec, count * sizeof(MyStruct));
    
    strcpy((*vec)[count-1].line, line);

    char lineCopy[nMax];
    strcpy(lineCopy, line);

    char* token = strtok(lineCopy, del);
    findDel(line, del, dels);

    while(token != NULL){
      n++;
      findIndex(line, token, (*vec)[count-1].tokens, n - 1);
      token = strtok(NULL, del);
    }

    (*vec)[count-1].n = n;
    strcpy((*vec)[count-1].dels, dels);
  }

  *size = count;
  fclose(input);
}

void findDel(char* line, char* del, char* dels) {
  int count = 0;

  for (int i = 0; i < strlen(line); i++) {
    if (strchr(del, line[i]) != NULL) {
      if (strchr(dels, line[i]) == NULL) {
        dels[count++] = line[i];
      }
    }
  }

  dels[count] = '\0';
}

void findIndex(char* line, char* token, int tokens[nMax][2], int n){
  char* p = strchr(line, token[0]);
  tokens[n][0] = (int)(p - line);
  p = strchr(line, token[strlen(token)-1]);
  tokens[n][1] = (int)(p - line);
}

void printStruct(MyStruct* vec, int size){
  for(int i = 0; i < size; i++){
    printf("{%s, %d, [%d %d], [%s]", vec[i].line, vec[i].n, vec[i].tokens[0][0], vec[i].tokens[0][1], vec[i].dels);
  }
}
