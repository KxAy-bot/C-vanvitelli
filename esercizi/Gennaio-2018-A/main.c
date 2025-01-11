#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define nMax 100

typedef struct {
  char c;
  float frequency;
  int* vec;
  int vecDim;
  int occ;
} MyStruct;

void printArray(int* array, int dim);
void readFromFile(char** string, int* len, const char* filename);
void saveUniqueChars(char* string, int len, char** uniqueChars, int* uniqueLen);
float charFrequency(char* string, int len, char c);
void getIndexes(char* string, int len, char c, int** indexVec, int* indexDim);
void fillStruct(MyStruct** vec, int* vecDim, char* string, int len);
void deleteDupes(char* string);
void shiftString(char* string, int index, int* len);
void printStruct(MyStruct* vec, int vecDim);

int main() {
  char* string = NULL;
  int len = 0;
  MyStruct* vec = NULL;
  int vecDim;

  readFromFile(&string, &len, "input.txt");
  fillStruct(&vec, &vecDim, string, len);
  printStruct(vec, vecDim);

  for (int i = 0; i < vecDim; i++) {
    free(vec[i].vec);
  }

  free(string);
  free(vec);

  return 0;
}

void readFromFile(char** string, int* len, const char* filename) {
  FILE *input = fopen(filename, "r");

  if (input == NULL) {
    exit(1);
  }

  fseek(input, 0, SEEK_END);
  *len = ftell(input);
  fseek(input, 0, SEEK_SET);

  *string = malloc(*len * sizeof(char));

  if (*string == NULL) {
    free(*string);
    exit(1);
  }

  fgets(*string, *len, input);
  fclose(input);
}

void saveUniqueChars(char* string, int len, char** uniqueChars, int* uniqueLen) {
  *uniqueChars = malloc(len * sizeof(char));

  if (*uniqueChars == NULL) {
    exit(1);
  }

  int index = 0;
  bool isUnique;
  for (int i = 0; i < len; i++) {
    isUnique = true;
    for (int j = 0; j < len; j++) {
      if (string[i] == string[j] && i != j) {
        isUnique = false;
      }
    }

    if (isUnique) {
      (*uniqueChars)[index++] = string[i];
    }
  }

  *uniqueLen = index;
  (*uniqueChars)[index] = '\0';

  (*uniqueChars) = realloc(*uniqueChars, index * sizeof(char));

  if (*uniqueChars == NULL) {
    free(*uniqueChars);
    exit(1);
  }
}

float charFrequency(char* string, int len, char c) {
  int count = 0;
  for (int i = 0; i < len; i++) {
    if (string[i] == c) {
      count++;
    }
  }

  return (float)count / len;
}

void getIndexes(char* string, int len, char c, int** indexVec, int* indexDim) {
  int index = 0;
  *indexVec = malloc(len * sizeof(int));
  for (int i = 0; i < len; i++) {
    if (string[i] == c) {
      (*indexVec)[index++] = i;
    }
  }

  (*indexDim) = index;
  (*indexVec) = realloc(*indexVec, index * sizeof(int));
  if (*indexVec == NULL) {
    free(*indexVec);
    exit(1);
  }
}

void printArray(int* array, int dim) {
  for (int i = 0; i < dim; i++) {
    printf("%d, ", array[i]);
  }
  printf("\n");
}

void fillStruct(MyStruct** vec, int* vecDim, char* string, int len) {
  (*vec) = malloc(len * sizeof(MyStruct));

  if (*vec == NULL) {
    exit(1);
  }

  char* copy = malloc((strlen(string) + 1) * sizeof(char));
  strcpy(copy, string);
  deleteDupes(copy);
  int copyLen = strlen(copy);

  int index = 0;
  int* indexVec = NULL;
  int indexDim = 0;

  for (int i = 0; i < copyLen; i++) {
    indexVec = NULL;
    indexDim = 0;
    (*vec)[index].c = copy[i];
    (*vec)[index].frequency = charFrequency(string, len, copy[i]);
    getIndexes(string, len, copy[i], &indexVec, &indexDim);

    (*vec)[index].vec = malloc(indexDim * sizeof(int));
    if ((*vec)[index].vec == NULL) {
      exit(1);
    }

    for (int j = 0; j < indexDim; j++) {
      (*vec)[index].vec[j] = indexVec[j];
    }
    (*vec)[index].vecDim = indexDim;
    index++;
  }

  (*vecDim) = index;
  (*vec) = realloc(*vec, index * sizeof(MyStruct));
  if (*vec == NULL) {
    free(*vec);
    free(indexVec);
    exit(1);
  }

  free(copy);
  free(indexVec);
}

void deleteDupes(char* string) {
  int len = strlen(string);
  for (int i = 0; i < len; i++) {
    for (int j = i + 1; j < len; j++) {
      if (string[i] == string[j]) {
        shiftString(string, j, &len);
        j--;
      }
    }
  }
}

void shiftString(char* string, int index, int* len) {
  for (int i = index; i < *len - 1; i++) {
    string[i] = string[i + 1];
  }
  string[*len - 1] = '\0';
  (*len)--;
}

void printStruct(MyStruct* vec, int vecDim) {
  for (int i = 0; i < vecDim; i++) {
    printf("{'%c', %f, [", vec[i].c, vec[i].frequency);
    for (int j = 0; j < vec[i].vecDim; j++) {
      printf("%d ", vec[i].vec[j]);
    }
    printf("]}\n");
  }
}
