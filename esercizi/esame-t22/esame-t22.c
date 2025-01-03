#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int tempo;
  float frequenza;
  float sonno;
  int agitazione;
} MyStruct;

typedef struct{
  int tempo;
  int tempoPrecedente;
  float frequenza;
  int presenza;
  int presenzaPrecedente;
  int movimento;
} Metrics;

void readFromFile(Metrics *array, int *size, const char* filename);
void evilAngeloMigliaccio(Metrics *dataArray, int dataSize, MyStruct *vec, int *dim);
void removeSpaces(char* string);
void printMetrics(Metrics *array, int size);
void printMyStruct(MyStruct *array, int size);

int main(){
  Metrics dataArray[100];
  MyStruct vec[100];
  int size = 0;
  int dim = 0;

  readFromFile(dataArray, &size, "input.txt");
  evilAngeloMigliaccio(dataArray, size, vec, &dim);
  printMyStruct(vec, dim);
  return 0;
}

void removeSpaces(char* string){
  size_t len = strlen(string);
  int counter = 0;
  for(int i = 0; i < len; i++){
    if(string[i] != ' '){
      string[counter++] = string[i];
    }
  }
  string[counter] = '\0';
}

void readFromFile(Metrics *array, int *size, const char* filename){
  FILE *input = fopen(filename, "r");

  if(input == NULL){
    printf("Errore nell'aprire il file\n");
    exit(1);
  }

  char line[256];
  int counter = 0;

  while(fgets(line, sizeof(line), input) != NULL){
    removeSpaces(line);

    char* token = strtok(line, ",");
    int tokenCounter = 0;

    while(token != NULL){
      if(tokenCounter == 0) {
        array[counter].tempo = atoi(token);
        counter > 0 ? array[counter].tempoPrecedente = array[counter-1].tempo : -1;
      }
      if(tokenCounter == 1) {array[counter].frequenza = atof(token);}
      if(tokenCounter == 2) {array[counter].presenza = atoi(token);}
      if(tokenCounter == 3) {array[counter].movimento = atoi(token);}
      tokenCounter++;
      token = strtok(NULL, ",");
    }

    counter++;
  }

  *size = counter;
}

void printMetrics(Metrics *array, int size){
  for(int i = 0; i < size; i++){
    printf("%d %d %f %d %d\n", array[i].tempo, array[i].tempoPrecedente, array[i].frequenza, array[i].presenza, array[i].movimento);
  }
}

void evilAngeloMigliaccio(Metrics *dataArray, int dataSize, MyStruct *vec, int *dim){
  int index = 0;
  int lastTimePresenza = -1;
  int prevPresenza = 0;
  int agitazione = 0;
  int intervalloPresenza = 0;
  int prevTimePresenza = 0;
  int lockIn = 0;

  for(int i = 0; i < dataSize; i++){

    if(dataArray[i].presenza == 1 && prevPresenza == 0){
      lastTimePresenza = dataArray[i].tempo;
    }
    
    prevPresenza = dataArray[i].presenza;

    if(dataArray[i].movimento == 1){
      agitazione++;
    }

    if(dataArray[i].presenza == 1){
      intervalloPresenza += dataArray[i].tempo - prevTimePresenza;
      prevTimePresenza = dataArray[i].tempo;
    }

    if(abs(dataArray[i].tempo - lastTimePresenza) >= 300){
      vec[index].tempo = dataArray[i].tempo;
      vec[index].frequenza = dataArray[i].frequenza;
      vec[index].agitazione = agitazione;
      vec[index].sonno = (float)intervalloPresenza / (float)(dataArray[i].tempo - dataArray[0].tempo); 
      index++;
    }
  }

  (*dim) = index;
}

void printMyStruct(MyStruct *array, int size){
  for(int i = 0; i < size; i++){
    printf("%d %f %f %d\n", array[i].tempo, array[i].frequenza, array[i].sonno, array[i].agitazione);
  }
}
