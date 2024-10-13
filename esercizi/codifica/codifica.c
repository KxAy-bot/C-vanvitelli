#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int codifica_binaria_decimale(int vBinario[], int base, int size);
int calcola_byte(int n);
int *codifica_decimale_binaria(int n, int *size);
void print_array(int *array, int size);
int *n_to_arr(int n, int *size);

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Non hai inserito abbastanza argomenti");
    exit(1);
  }

  int size;

  int n = atoi(argv[1]);
  char codifica = argv[2][0];
  int sistema = 0;

  if (codifica != 'b' && argc >= 4) {
    sistema = atoi(argv[3]);
  }

  if (sistema != 0) {
    int *vBinario = n_to_arr(n, &size);
    printf("%d\n", codifica_binaria_decimale(vBinario, sistema, size));
    free(vBinario);
  } else {
    int *array = codifica_decimale_binaria(n, &size);
    print_array(array, size);
    free(array);
  }

  return 0;
}

int *codifica_decimale_binaria(int n, int *size) {
  *size = calcola_byte(n);

  int *binario = (int *)malloc(*size * sizeof(int));

  if (binario == NULL) {
    printf("errore durante allocazione della memoria\n");
    exit(1);
  }

  for (int i = *size - 1; i >= 0; i--) {
    binario[i] = n % 2;
    n /= 2;
  }

  return binario;
}

int calcola_byte(int n) {
  if (n == 0)
    return 1;
  return (int)log2(n) + 1;
}

int codifica_binaria_decimale(int vBinario[], int base, int size) {
  int n = 0;
  for (int k = size; k > 0; k--) {
    n += vBinario[k - 1] * (int)pow(base, (double)size - k);
  }
  return n;
}

void print_array(int *array, int size) {
  for (int i = 0; i < size; i++) {
    printf("%d", array[i]);
  }
}

int *n_to_arr(int n, int *size) {
  *size = (int)log10(n) + 1;
  int i = *size - 1;

  int *array = (int *)malloc(*size * sizeof(int));

  do {
    array[i] = n % 10;
    n /= 10;
    i--;
  } while (n != 0);

  return array;
}
