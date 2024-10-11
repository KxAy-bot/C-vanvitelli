#include <stdio.h>
#include <stdbool.h>

bool is_even(int n);

int main() {
  int A;
  int B;
  int steps = 0;
  
  FILE *pReadFile = fopen("input.txt", "r");
  fscanf(pReadFile, "%d %d", &A, &B);
  fclose(pReadFile);

  printf("%d %d", A, B);

  while (A != 1 || B != 1){
    if(is_even(A) && is_even(B))
    {

      A /= 2;
      B /= 2;
      
    } 
    else if(!is_even(A) && !is_even(B))
    {

      A = 2 * A + 1;
      B = 2 * B + 1;

    } 
    else if(!is_even(B))
    {
      A += 3;
    } 
    else if(!is_even(A))
    {
      B += 3;
    }
    else 
    {
      steps = -1;
      break;
    }
    steps++;
  }

  FILE *pWriteFile = fopen("output.txt", "w");
  fprintf(pWriteFile, "%d\n", steps);
  fclose(pWriteFile);

  return 0;
}

bool is_even(int n){
  return n % 2;
}
