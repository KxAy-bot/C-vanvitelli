#include <stdio.h>
#include <math.h>

#define PI 3.14159
#define X 150
#define Y 50

void h_write_cosin(FILE *pF, int cos_values[]);
void v_write_cosin(FILE *pF, int cos_values[]);

int main(){
    FILE *pF = fopen("cosinusoide.txt", "w");

    int cos_values[X], i, opzione;

    printf("Come vuoi la cosinusoide: \n1: orizzontale\n2: verticale\n\n Digita il numero corrispondente: ");
    scanf("%d", &opzione);

    for(i = 0; i < X; i++){
        double angle = (PI * 2 * i) / X;
        cos_values[i] = round((cos(angle) + 1) * ((float)Y/2));
    }

    if(opzione == 1){
        h_write_cosin(pF, cos_values);
    } else{
        v_write_cosin(pF, cos_values);
    }

    return 0;
}

void h_write_cosin(FILE *pF, int cos_values[]){
    int j, i;

    for(j = Y; j >= 0; j--){
        for(i = 0; i < X; i++){
            if(cos_values[i] == j){
                fprintf(pF, "*");
            } else{
                fprintf(pF," ");
            }
        }
        fprintf(pF, "\n");
    }

    fclose(pF);
}

void v_write_cosin(FILE *pF, int cos_values[]){
    int j, i;

    for(i = 0; i < X; i++){
        for(j = 0; j < cos_values[i];j++){
            fprintf(pF," ");
        }
        fprintf(pF,"*\n");
    }

    fclose(pF);
}
