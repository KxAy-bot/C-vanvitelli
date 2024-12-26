#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define nMax 100

typedef struct {
  char line[nMax];
  int n;
  char tokens[nMax][nMax];
} MyStruct;

void fillStruct(MyStruct **vec, char* filename);
char* reorderedLine(char* line);
void orderToken(char* token);

int main(){
  MyStruct *vec = NULL;
  fillStruct(&vec, "input.txt");

  free(vec);
  return 0;
}

void fillStruct(MyStruct **vec, char* filename){
  FILE *input = fopen(filename, "r");

  if(input == NULL){
    printf("Errore durante apertura del file\n");
    exit(1);
  }

  char line[nMax];
  int n = 0;

  while(fgets(line, nMax, input) != NULL){
    n++;
    if(*vec == NULL){
      *vec = malloc(sizeof(MyStruct));
    } else{
      *vec = realloc(*vec, sizeof(MyStruct) * n);
    }

    reorderedLine(line);
  }

  fclose(input);
}

char* reorderedLine(char* line){
  char* token = strtok(line, "  ");
  
  while(token != NULL){
    token = strtok(NULL, "  ");
  }

  return "";
}

void reorderToken(char* token){
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
