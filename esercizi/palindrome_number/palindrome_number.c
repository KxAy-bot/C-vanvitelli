#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool isPalindrome(int x);

int main() {
  int x ;
  printf("Inserisci un numero");
  scanf("%d", &x);
  int result = isPalindrome(x);

  printf("%s", result ? "true" : "false");
  return 0;
}

int countDigits(int n) { return floor(log10(n) + 1);}

bool isPalindrome(int x) {
  if (x < 0)
    return false;
  if(x > 0 && x % 10 == 0)
    return false;

  int temp = x, i = countDigits(x), n = 0;

  while (temp > 0) {
    printf("ciclo %d: %d\n", i, n);
    n += (int)(temp % 10) * pow(10, i - 1);
    temp /= 10;
    i--;
  }

  printf("%d %d", n, x);

  printf("\n\nn: %d\n", n);
  return n == x ? true : false;
}
