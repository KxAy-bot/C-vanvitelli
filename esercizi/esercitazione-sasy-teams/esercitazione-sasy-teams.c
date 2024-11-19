#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int n_val_sinistra;
  int n_val_destra;
  int somma;
} MyStruct;

void setVet(MyStruct *vettore, int index, int n_val_sinistra, int n_val_destra,
            int somma);
void fillStruct(MyStruct **vettore, const char *filename, int *size);
void printStruct(MyStruct *vettore, int size);
int calculateSum(const char *string);
int calculateDigits(const char *string);
void reoderStruct(MyStruct *vettore, int size);
void saveStruct(MyStruct *vettore, int size, const char *filename);

int main() {
  MyStruct *vettore = NULL;
  int size;

  fillStruct(&vettore, "input.txt", &size);
  reoderStruct(vettore, size);
  printStruct(vettore, size);
  saveStruct(vettore, size, "output.bin");
  return 0;
}

void setVet(MyStruct *vettore, int index, int n_val_sinistra, int n_val_destra,
            int somma) {
  vettore[index].n_val_destra = n_val_destra;
  vettore[index].n_val_sinistra = n_val_sinistra;
  vettore[index].somma = somma;
}

void fillStruct(MyStruct **vettore, const char *filename, int *size) {
  FILE *input = fopen(filename, "rb");
  char line[100];
  int count = 0;

  if (input == NULL) {
    printf("Errore durante apertura del file\n");
    exit(-1);
  }

  while (fgets(line, sizeof(line), input) != NULL) {
    count++;
    *vettore = realloc(*vettore, count * sizeof(MyStruct));

    if (*vettore == NULL) {
      printf("Errore di allocazione della memoria\n");
      fclose(input);
      exit(-1);
    }

    setVet(*vettore, count - 1, 0, 0, 0);

    char *leftPart = strtok(line, "=");
    char *rightPart = strtok(NULL, "=");

    int somma = calculateSum(leftPart);
    int sommaRight = calculateSum(rightPart);
    if (somma == sommaRight) {
      int n_val_sinistra = calculateDigits(leftPart);
      int n_val_destra = calculateDigits(rightPart);
      setVet(*vettore, count - 1, n_val_sinistra, n_val_destra, somma);
    } else {
      vettore = realloc(*vettore, (count - 2) * sizeof(MyStruct));
      count--;
    }
  }

  fclose(input);
  *size = count;
}

int calculateSum(const char *string) {
  char temp[strlen(string)];
  strcpy(temp, string);

  int somma = 0, count = 0;
  char *buffer = strtok(temp, "+");

  while (buffer != NULL) {
    somma += atoi(buffer);
    buffer = strtok(NULL, "+");
    count++;
  }

  return somma;
}

int calculateDigits(const char *string) {
  char temp[strlen(string)];
  strcpy(temp, string);

  if (strtok(temp, "+") == NULL) {
    return 0;
  }

  int count = 1;

  while (strtok(NULL, "+") != NULL)
    count++;

  return count;
}

void printStruct(MyStruct *vettore, int size) {
  for (int i = 0; i < size; i++) {
    printf("{%d, %d, %d}\n", vettore[i].n_val_sinistra, vettore[i].n_val_destra,
           vettore[i].somma);
  }
}

void reoderStruct(MyStruct *vettore, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = i + 1; j < size; j++) {
      if (vettore[i].somma < vettore[j].somma) {
        MyStruct temp = vettore[i];
        vettore[i] = vettore[j];
        vettore[j] = temp;
      }
    }
  }
}

void saveStruct(MyStruct *vettore, int size, const char *filename) {
  FILE *output = fopen(filename, "wb");

  if (output == NULL) {
    printf("Errore durante apertura del file\n");
    exit(-1);
  }

  fwrite(vettore, sizeof(MyStruct), size, output);

  fclose(output);
}
