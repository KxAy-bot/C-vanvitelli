#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct {
  int numero;
  int somma_riga;
  int numero_occorrenze_1;
} MyStruct;

typedef struct {
  char *numero;
  int valore;
} Convertitore;

int findValue(Convertitore *tabella, char *key);
void fillStruct(MyStruct **vettore, int *dim, Convertitore *tabella,
                const char *filename);
void setVet(MyStruct *vettore, int index, int numero, int somma_riga,
            int numero_occorrenze_1);
void printVet(MyStruct *vettore, int dim);
void reoderVet(MyStruct* vettore, int dim);
void saveToFile(MyStruct* vettore, int dim, const char* filename);

int main() {
  Convertitore tabella[] = {
      {"uno", 1}, {"due", 2},   {"tre", 3},  {"quattro", 4}, {"cinque", 5},
      {"sei", 6}, {"sette", 7}, {"otto", 8}, {"nove", 9},    {"dieci", 10},
  };

  MyStruct *vettore = NULL;
  int dim;

  fillStruct(&vettore, &dim, tabella, "input.txt");
  reoderVet(vettore, dim);
  printVet(vettore, dim);
  saveToFile(vettore, dim, "output.bin");

  return 0;
}

int findValue(Convertitore *tabella, char *key) {
  for (int i = 0; i < SIZE; i++) {
    if (strcmp(key, tabella[i].numero) == 0) {
      return tabella[i].valore;
    }
  }
  return -1;
}

void fillStruct(MyStruct **vettore, int *dim, Convertitore *tabella,
                const char *filename) {
  FILE *input = fopen(filename, "rb");
  int count = 0;
  char line[256];

  while (fgets(line, sizeof(line), input) != NULL) {
    count++;
    *vettore = realloc(*vettore, count * sizeof(MyStruct));
    char *token = strtok(line, " ");

    int numero = 0;
    int somma_riga = 0;
    int numero_occorrenze_1 = 0;

    setVet(*vettore, count - 1, numero, somma_riga, numero_occorrenze_1);

    while (token != NULL) {
      int value = findValue(tabella, token);

      if (value != -1) {
        numero = numero * 10 + value;
        somma_riga += value;
      }

      if (value == 1) {
        numero_occorrenze_1++;
      }

      token = strtok(NULL, " ");
    }
    setVet(*vettore, count - 1, numero, somma_riga, numero_occorrenze_1);
  }

  (*dim) = count;
  fclose(input);
}

void setVet(MyStruct *vettore, int index, int numero, int somma_riga,
            int numero_occorrenze_1) {
  vettore[index].numero = numero;
  vettore[index].somma_riga = somma_riga;
  vettore[index].numero_occorrenze_1 = numero_occorrenze_1;
}

void printVet(MyStruct *vettore, int dim) {
  for (int i = 0; i < dim; i++) {
    printf("{%d, %d, %d}\n", vettore[i].numero, vettore[i].somma_riga,
           vettore[i].numero_occorrenze_1);
  }
}

void reoderVet(MyStruct* vettore, int dim){
  for(int i = 0; i < dim - 1; i++){
    for(int j = i + 1; j < dim; j++){
      if(vettore[i].numero < vettore[j].numero){
        MyStruct temp = vettore[i];
        vettore[i] = vettore[j];
        vettore[j] = temp;
      }
    }
  }
}

void saveToFile(MyStruct* vettore, int dim, const char* filename){
  FILE* output = fopen(filename, "wb");

  if(output == NULL){
    printf("errore durante scrittura file binario");
    exit(-1);
  }

  fwrite(vettore, sizeof(MyStruct), dim, output);
  fclose(output);
}
