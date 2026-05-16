#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "constants.h"

void Addition(char file[]);
void AllData(char file[STRING_SIZE]);
void SomeData(char file[STRING_SIZE]);
  
int main(int argc, char *argv[]){
  // <Setting things up>
  char Command;
  char file[1024]="RESULTS";
  srand(time(NULL));  // seed with current time
  //while 1:Menu(Func=[Addition,AllData,SomeData,quit,ChangeFile],Arg=[file,file,file],INP="Enter: 0 to take the test, 1 to view all scores, 2 to view specific scores, 3 to quit, or 4 to change the source file")
  while (true){
    char input[STRING_SIZE]
;   printf("Enter: 0 to take the test, 1 to view all scores, 2 to view specific scores, 3 to quit, or 4 to change the source file: ")
    // Get user input; raising an error if fgets returns NULL.
;   if (fgets(input, STRING_SIZE, stdin)==NULL)   {fprintf(stderr,"Error reading input.\n");input[0]='\0';}
;   Command=input[0]
;   switch (Command){
      case '0':
        Addition(file);
        break;
      case '1':
        AllData(file);
        break;
      case '2':
        SomeData(file);
        break;
      case '3':
        return 0;
        break;
      case '4':
        ;printf("Enter filename: ")
        ;if (fgets(file, 1024, stdin)==NULL)   {fprintf(stderr,"Error reading input.\n");return 1;}
        ;break;}
    };}


