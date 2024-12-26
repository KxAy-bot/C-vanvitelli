#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nMax 100

typedef struct {
  char line[nMax];
  int n;
  char tokens[nMax][nMax];
} MyStruct;

void fillStruct(MyStruct **vec, char* filename, int* dim);
char* reorderedLine(char* line, int* wordCount);
void orderToken(char* token);
void fillTokens(MyStruct *vec, int n, char* line);
void printStruct(MyStruct *vec, int n);
void writeStruct(MyStruct *vec, int dim, char* filename);

int main(){
  MyStruct *vec = NULL;
  int dim = 0;
  fillStruct(&vec, "input.txt", &dim);

  printStruct(vec, dim);

  writeStruct(vec, dim, "output.bin");
  free(vec);
  return 0;
}

void fillStruct(MyStruct **vec, char* filename, int* dim){
  FILE *input = fopen(filename, "r");

  if(input == NULL){
    printf("Errore durante apertura del file\n");
    exit(1);
  }

  char line[nMax];
  int n = 0, wordCount = 0;

  while(fgets(line, nMax, input) != NULL){
    n++;
    if(*vec == NULL){
      *vec = malloc(sizeof(MyStruct));
    } else{
      *vec = realloc(*vec, sizeof(MyStruct) * n);
    }
    
    if(*vec == NULL){
      printf("porcodio");
      exit(1);
    }

    fillTokens(*vec, n, line);
    char* newLine = reorderedLine(line, &wordCount);
    strcpy((*vec)[n - 1].line, newLine);
    (*vec)[n - 1].n = wordCount;
  }

  *dim = n;
  fclose(input);
}

char* reorderedLine(char* line, int* wordCount){
  int len = strlen(line);
  char* result = malloc((len + 1) * sizeof(char));

  if(!result){
    printf("Errore durante l'allocazione della memoria\n");
    exit(1);
  }

  result[0] = '\0';

  char* lineCopy = strdup(line);

  if(!lineCopy){
    printf("Errore durante l-allocazione della memoria");
    free(result);
    exit(1);
  }

  char* token = strtok(lineCopy, " ");
  *wordCount = 0;

  while(token != NULL){
    (*wordCount)++;
    orderToken(token);
    strcat(result, token);
    strcat(result, " ");
    token = strtok(NULL, " ");
  }

  free(lineCopy);

  int resultLen = strlen(result);

  if(resultLen > 0 && result[resultLen - 1] == ' '){
    result[resultLen - 1] = '\0';
  }

  return result;
}

void orderToken(char* token){
  int n = strlen(token);
  for(int i = 0; i < n; i++){
    for(int j = i + 1; j < n; j++){
      if(token[i] > token[j]){
        char tmp = token[i];
        token[i] = token[j];
        token[j] = tmp;
      }
    }
  }
}

void fillTokens(MyStruct *vec, int n, char* line) {
  char* lineCopy = strdup(line); 
  char* token = strtok(lineCopy, " ");
  int index = 0;

  while (token != NULL) {

    strcpy(vec[n - 1].tokens[index], token);
    vec[n - 1].tokens[index][strlen(vec[n-1].tokens[index])] = '\0'; // Assicura il null-terminator

    token = strtok(NULL, " ");
    index++;
  }

  free(lineCopy); 
}

void printStruct(MyStruct *vec, int n){
  for(int i = 0; i < n; i++){
    printf("{%s, %d, [", vec[i].line, vec[i].n);
    for(int j = 0; j < vec[i].n; j++){
      printf("%s, ", vec[i].tokens[j]);
    }
    printf("]}\n");
  }
}

void writeStruct(MyStruct *vec, int dim, char* filename){
  FILE *output = fopen(filename, "w");

  if(!output || !vec){
    printf("Errore durante l'apertura del file\n");
    exit(1);
  } 

  fwrite(vec, sizeof(MyStruct), dim, output);
  fclose(output);
}
