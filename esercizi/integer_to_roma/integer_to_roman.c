#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* intToRoman(int num);

int main() {
  int numero; 
  printf("Inserisci il numero da convertire: ");
  scanf("%d", &numero);

  printf("\nRisultato: %s", intToRoman(numero));
  return 0;
}

typedef struct {
  char* c;
  int value;
} Map;

int searchIndex(Map* Map, int value, int size){
  for(int i = 0; i < size; i++){
    if(Map[i].value == value){
      return i;
    }
  }
  return -1;
}

char* intToRoman(int num) {
  Map Map[] = {
    {"M", 1000},
    {"CM", 900},
    {"D", 500},
    {"CD", 400},
    {"C", 100},
    {"XC", 90},
    {"L", 50},
    {"XL", 40},
    {"X", 10},
    {"IX", 9},
    {"V", 5},
    {"IV", 4},
    {"I", 1}
  };
  int size = sizeof(Map) / sizeof(Map[0]);
  char* roman = (char*)malloc(20 * sizeof(char));
  int index = 0, i = -1;

  while(num > 0){
    if(num >= Map[++i].value){
      printf("%d\n", Map[i].value);
      strcpy(&roman[index], Map[i].c);
      index += strlen(Map[i].c);
      num -= Map[i].value;
      i = -1;
    }
  }

  roman[index] = '\0';

  return roman;
}
