#include <stdio.h>
#define MAX 100

// FATTO PROGRAMMANDO UNA SORTA DI HASHMAP, VOLEVO UNA SOLUZIONE PIU SIMPATICA.
//
//
// Realizzare un sottoprogramma che data una stringa ne crei una seconda che
// contenga i caratteri della prima, presi una sola volta,§ ognuno seguito dal
// proprio numero di occorrenze (si su;pponga il numero di occorrenze sempre
// <10).
//

typedef struct {
  char character;
  int count;
} Map;

int slen(char *string) {
  int i = -1;
  while (string[++i] != '\0')
    ;
  return i;
}

void add(Map *Map, char key, int size) {
  for (int i = 0; i < size; i++) {
    if (Map[i].character == key) {
      Map[i].count++;
      return;
    }
  }
  for (int i = 0; i < size; i++) {
    if (Map[i].character == '\0') {
      Map[i].character = key;
      Map[i].count = 1;
      return;
    }
  }
}

void strcifre(char *s1, char *s2) {
  int len = slen(s1);
  Map Map[len];

  for (int i = 0; i < len; i++) {
    Map[i].character = '\0';
    Map[i].count = 0;
  }

  for (int i = 0; i < len; i++) {
    add(Map, s1[i], len);
  }

  int size = sizeof(Map) / sizeof(Map[0]);

  int index = 0;
  for (int i = 0; i < len; i++) {
    if (Map[i].character != '\0') {
      s2[index++] = Map[i].character;
      s2[index++] = '0' + Map[i].count;
    }
  }
  s2[index] = '\0';
}

int main() {
  char s1[MAX];

  printf("Inserisci la stringa: ");
  fgets(s1, MAX, stdin);

  char s2[slen(s1)];

  strcifre(s1, s2);

  printf("\n\n%s", s2);
  return 0;
}
