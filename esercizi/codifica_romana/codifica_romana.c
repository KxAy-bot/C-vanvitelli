#include <stdio.h>
#include <string.h>

int romanToInt(char *s);

int main() {
  char romano[] = "MCMXCIV";

  printf("%d", romanToInt(romano));
  return 0;
}

typedef struct {
  char key;
  int value;
} Map;

int linear_search(Map *Map, size_t size, const char key) {
  for (size_t i = 0; i < size; i++) { 
    if (Map[i].key == key) {
      return Map[i].value;
    }
  }
  return -1;
}

int romanToInt(char *s) {
  int length = strlen(s), res = 0;
  Map romanTable[] = {
    {'I', 1},   {'V', 5},   {'X', 10},   {'L', 50},
    {'C', 100}, {'D', 500}, {'M', 1000}, {'N', 0},
  };
  size_t size = sizeof(romanTable) / sizeof(Map);

  for(int i = 0; i < length; i++){
    int current = linear_search(romanTable, size, s[i]);
    int next = linear_search(romanTable, size, s[i + 1]);

    // printf("current: %d, next: %d\n\n", current, next);

    if(current < next && next != -1 && current != 0){
      res += (next - current);
      s[i + 1] = 'N';
    } else{
      res += current;
    }

  }
  return res;
}
