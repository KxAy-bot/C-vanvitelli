#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N_MAX 100
#define MAX 1000

typedef struct {
  int id;
  int chars;
  int words;
  float meanc;
  float meanw;
} Mystruct;

void printStruct(Mystruct* vettore, int size){
  for(int i = 0; i < size; i++){
    printf("{%d %d %d %.2lf %.2lf}\n", vettore[i].id, vettore[i].chars, vettore[i].words, vettore[i].meanc, vettore[i].meanw);
  }
}

int readTextFile(char* string){
  FILE *fptr = fopen("input.txt", "rb");

  if(fptr == NULL){
    printf("Errore durante apertura del file");
    return -1;
  }

  fread(string, sizeof(char), MAX, fptr);
  fclose(fptr);
  return 0;
}

void saveStruct(Mystruct* vettore, int size){
  FILE *fptr = fopen("output.bin", "wb");

  if(fptr == NULL){
    printf("Errore durante la scrittura del file binario (tha supreme nudo)");
    return;
  }

  fwrite(vettore, sizeof(Mystruct), size, fptr);
  fclose(fptr);

  printf("Salvata struttura del file .bin");
}

void fillStruct(Mystruct* vettore, int id, int chars, int words, float meanc, float meanw){
    vettore[id].id = id;
    vettore[id].chars = chars;
    vettore[id].words = words;
    vettore[id].meanc = meanc;
    vettore[id].meanw = meanw;
}

void sortStruct(Mystruct* vettore, int size){
  for(int i = 0; i < size - 1; i++){
    for(int j = i + 1; j < size; j++){
      if(vettore[i].chars < vettore[j].chars){
        Mystruct temp = vettore[i];
        vettore[i] = vettore[j];
        vettore[j] = temp;
      }
    }
  }
}

int countCharacters(char* string){
  int count = 0, index = 0;
  while(string[index++] != '\0'){
    count++;
  }
  return count;
}

int countWords(char* string){
  int count = 0, activeWord = 0;
  for(int i = 0; string[i] != '\0'; i++){
    if(string[i] == ' ')
      activeWord = 0;
    else if(!activeWord){
      activeWord = 1;
      count++;
    }
  }
  return count;
}

void textParser(char* string, const char* delimiter, Mystruct* vettore, int* size){
  int index = 0, chars = 0, words = 0, bufChars = 0, bufWords = 0;
  float meanc = 0, meanw = 0;
  char* tok = strtok(string, delimiter);

  while(tok != NULL){
    /*printf("%d)\t%s\n", index, tok);*/
    /*printf("caratteri frase %d: %d\n\n", index, countCharacters(tok));*/
    /*printf("parole frase %d: %d\n\n", index, countWords(tok));*/
    words = countWords(tok);
    chars = countCharacters(tok);
    bufWords += words;
    bufChars += chars;
    meanc = (float)bufChars / (float)(index + 1);
    meanw = (float)bufWords / (float)(index + 1);
    /*printf("Index %d: words: %d, chars: %d, meanc: %.2lf, meanw: %.2lf", index, words, chars, meanc, meanw);*/
    tok = strtok(NULL, delimiter);

    fillStruct(vettore, index, chars, words, meanc, meanw);
    index++;
  }

  *size = index;
}

int main(){
  int size = 0;
  char string[MAX];
  Mystruct vettore[N_MAX];

  if(readTextFile(string) == -1){
    return -1;
  }

  textParser(string, ".!?", vettore, &size);

  sortStruct(vettore, size);
  printf("\n");
  printStruct(vettore, size);

  saveStruct(vettore, size);

  return 0;
}
