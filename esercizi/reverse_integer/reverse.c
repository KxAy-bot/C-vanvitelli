#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int reverse(int x);

int main() {
  int num;
  printf("Inserisci il numero: ");
  scanf("%d", &num);

  printf("%d\n", reverse(num));
  return 0;
}

int reverse(int x) {
  int res = 0;
  while (x != 0) {
    int digit = x % 10;
    x /= 10;
    
    if (res > INT_MAX / 10 || (res == INT_MAX / 10 && digit > 7)) return 0;
    if (res < INT_MIN / 10 || (res == INT_MIN / 10 && digit < -8)) return 0;
    
    res = res * 10 + digit;
  }
  return res;
}
