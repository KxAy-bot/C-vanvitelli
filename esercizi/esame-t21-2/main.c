#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  int weekdays;
  int hours;
  float overlap; // durata totale in ore della sovrapposizione degli appuntamenti quel giorno nel mese
  float average; // media giornaliera delle ore prenotate quel giorno della settimana nell intero mese
} MyStruct;

typedef struct{
  int weekdays;
  int hours;
  int appHour;
  int appDuration;
  int count;
} Data;

typedef struct{
  char key[4];
  int value;
} List;

int findValue(List* Giorni, char* key);
void readFromFile(Data* datas, List* Giorni, const char* filename);
void fillStruct(MyStruct* vec, Data* datas);
void initStruct(MyStruct* vec);
void initData(Data* datas);
void printStruct(MyStruct* vec);
void saveToBin(MyStruct* vec);

int main(){
  List Giorni[7] = {
    {"LUN", 0},
    {"MAR", 1},
    {"MER", 2},
    {"GIO", 3},
    {"VEN", 4},
    {"SAB", 5},
    {"DOM", 6}
  };

  MyStruct vec[7];
  Data datas[7];

  initStruct(vec);
  initData(datas);
  readFromFile(datas, Giorni, "input.txt");
  fillStruct(vec, datas);
  printStruct(vec);
  saveToBin(vec);

  return 0;
}

int findValue(List* Giorni, char* key){
  for(int i = 0; i < 7; i++){
    if(strcmp(Giorni[i].key, key) == 0){
      return Giorni[i].value;
    }
  }
  return -1;
}

void initStruct(MyStruct* vec){
  for(int i = 0; i < 7; i++){
    vec[i].weekdays = 0;
    vec[i].hours = 0;
    vec[i].average = 0;
    vec[i].overlap = 0;
  }
}

void readFromFile(Data* datas, List* Giorni, const char* filename){
  FILE *input = fopen(filename, "r");

  if(input == NULL){
    printf("Errore durante apertura del file");
    exit(1);
  }

  char line[200];

  while(fgets(line, 200, input) != NULL){
    char key[4];
    int weekdays, day, appHour, appDuration;

    sscanf(line, "%s %d %d:%*d %d", key, &day, &appHour, &appDuration);
    weekdays = findValue(Giorni,key);

    datas[weekdays].weekdays = weekdays;
    datas[weekdays].appDuration = appDuration;
    datas[weekdays].hours += appDuration;
    datas[weekdays].appHour = appHour;
    datas[weekdays].count += 1;
  }

  fclose(input);
}

void initData(Data* datas){
  for(int i = 0; i < 7; i++){
    datas[i].count = 0;
    datas[i].weekdays = 0;
    datas[i].appHour = 0;
    datas[i].appDuration = 0;
    datas[i].hours = 0;
  }
}

void fillStruct(MyStruct* vec, Data* datas){
  for(int i = 0; i < 7; i++){
    vec[i].weekdays = datas[i].weekdays;
    vec[i].hours = datas[i].hours;
    vec[i].average = (float)datas[i].hours / (datas[i].count + 1);
    vec[i].overlap = datas[i].hours;
  }
}

void printStruct(MyStruct* vec){
  for(int i = 0; i < 7; i++){
    printf("{%d,%d,%f,%f}\n", vec[i].weekdays, vec[i].hours, vec[i].overlap, vec[i].average);
  }
}

void saveToBin(MyStruct* vec){
  FILE *output = fopen("output.bin", "wb");

  if(output == NULL){
    printf("Errore durante scrittura file binario");
    exit(1);
  }

  fwrite(vec, sizeof(MyStruct), 7, output);
}
