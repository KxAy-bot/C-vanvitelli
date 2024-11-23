#include <stdio.h>
#include <stdlib.h>

#define nMax 100

typedef struct{
  char line[nMax]; // linea del testo da dividere
  int n; // numero di token trovati
  int tokens[nMax][2]; // per ogni token trovato, contiene il primo e l-ultimo indice della lettera del token nella stringa
  char dels[nMax]; // contiene i soli delimitatori trovati nella stringa, presi una sola volta
} MyStruct;

int main(){
  return 0; 
}
