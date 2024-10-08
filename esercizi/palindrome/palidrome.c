#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int check_palindrome(char string[], int size);
int string_length(char *string);
int clear_and_get_spaces(char string[], int len);

int main(){
  char *string = NULL;
  size_t size = 0;

  printf("inserisci la frase: ");
  getline(&string, &size, stdin);

  int length = string_length(string);

  if(length > 0 && string[length - 1] == '\n'){
    string[length - 1] = '\0';
    length--;
  }

  int palidrome = check_palindrome(string, length);

  if(palidrome){
    printf("la frase non risulta palidrome");
  } else{
    printf("la frase risulta palidrome");
  }

  free(string);

  return 0; 
}

int string_length(char *string){
  int length = 0;
  while(string[length] != '\0'){
    length++;
  }
  return length;
}

int check_palindrome(char string[], int size){
  int spaces = clear_and_get_spaces(string, size);
  int len = size - spaces;
  for(int i = 0; i < len; i++){
    char current = string[i];
    char reverse = string[len - 1 - i];
    if(current != reverse){
      return true;
      break;
    } 
  }
  return false; 
}

int clear_and_get_spaces(char string[], int len){
  int spaces = 0;
  for(int i = 0; i < len; i++){
    if(string[i] == ' '){
      spaces++;
      for(int j = i; j < len; j++){
        string[j] = string[j + 1];
      }
    }
  }

  printf("%s\n", string);

  return spaces;
}
