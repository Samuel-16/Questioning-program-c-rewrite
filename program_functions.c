#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "structs.h"

static const struct StringArr StrArrInit={.Stri="",.next=NULL};
static const struct ByteArr ByteArrInit={.byte={0,0},.next=NULL};

static inline int DEZERO(int x){
  if (x!=0){return x;}
  else {return 1;}}

bool invalidName(char Name[]){
  //Invalid if: "0"in Name or"1"in Name or Name==""
  if (!isprint(Name[0])){return true;}
  for (short unsigned int i=0;i<STRING_SIZE;i++){
    switch (Name[i]){
      case '0':
        return true;
      case '1':
        return true;
      case '\0':
        return false;}}
  return true;}

unsigned int inStArr(struct StringArr *Arr, char i[]){
  unsigned int out=1;
  while (Arr!=NULL){
    if (strcmp(Arr->Stri,i)==0){return out;}
    Arr=Arr->next;
    out++;}
  return 0;}

struct ByteArr* scoreFromIndex(struct ByteArr *Arr,unsigned int index){
  unsigned int n=0;
  while (n<index && Arr->next!=NULL){
    Arr=Arr->next;
    n++;}
  return Arr;}

static int sanitise(char stri[]){
  if (invalidName(stri)){return 1;}
  unsigned short int n=0;
  while (stri[n]!='\0'){
    if (isprint(stri[n])&& stri[n]!='\n'){n++;}
    else{
      for (unsigned short int m=n; stri[m]!='\0' && m<=STRING_SIZE; m++){
        stri[m]=stri[m+1];}}}
  return 0;}

void Addition(char file[]){
  //R=["","","","",""]
  char R[5][STRING_SIZE];
  //R={"","","","",""}; // DOESN'T WORK.
  //File=open(file,"a")
  FILE *File;
  File=fopen(file,"a");
  if (!File){
    fprintf(stderr,"ERROR: File %s could not be created.\n",file);
    return;}
  /*Name=input("What is your name: ")
    while"0"in Name or"1"in Name or Name=="":Name=input("INVALID. Try again: ")
    File.write(Name)*/
  //getchar(); // Clean the input stream. // Unnecessary after changing `scanf` to fgets`
  char Name[STRING_SIZE];
  char Answer[STRING_SIZE];
  printf("What is your name: ");
  if (fgets(Name,STRING_SIZE,stdin)==NULL)   {fprintf(stderr,"Error reading input.\n");Name[0]='\0';}
  printf("\n");
  while (sanitise(Name)){ // `sanitise` runs invalidName(Name) while fixing `Name`, so it can go directly in the if.
    printf("INVALID. Try again: ");
    if (fgets(Name,STRING_SIZE,stdin)==NULL)   {fprintf(stderr,"Error reading input.\n");Name[0]='\0';}
    printf("\n");}
  fprintf(File,"%s",Name);
  //for i in range(5):
  for (unsigned char i=0;i<5;i++){
    /*No1=int(Rand()*8+1)
      No2=int(Rand()*8+1)*/
    unsigned char No1=rand()%8+1;
    unsigned char No2=rand()%8+1;
    //Guess=input("What is "+str(No1)+"+"+str(No2)+"? ")
    printf("What is %u+%u? ",No1,No2);
    //while len(Guess)>2 or len(Guess)==0 or 0 in (j in "0123456789" for j in Guess):Guess=input("Invalid. What is "+str(No1)+"+"+str(No2)+"?")
    // <Simplifying for the time being>
    if (fgets(Answer,STRING_SIZE,stdin)==NULL)   {fprintf(stderr,"Error reading input.\n");Name[0]='\0';}
    unsigned short int Guess;
    sscanf(Answer,"%hu", &Guess);
    // R[i]="1"if str(No1+No2)==Guess else"0"
    if (Guess==No1+No2){strcpy(R[i],"1");}
    else {strcpy(R[i],"0");}
    // File.write(R[i])
    fprintf(File,"%s",R[i]);}
  //File.close()
  fclose(File);
  //print("You got "+str(sum(int(i)for i in R)*20)+"%.")
  printf("You got %hu%%.\n",((atoi(R[0])+atoi(R[1])+atoi(R[2])+atoi(R[3])+atoi(R[4]))*20));}


void AllData(char file[STRING_SIZE]){
  /*File=open(file,"r")
    FTXT=File.read()
    File.close()*/ // python
  FILE *File;
  File=fopen(file,"r");
  if (!File){
    fprintf(stderr,"ERROR: File %s not found.\n",file);
    return;}
  //i,CuName,NameAr,ScoreAr=0,"",[],[] // python
  char i=fgetc(File); // `i` will be the current character being read from the file.
  unsigned char j=0; // `j` will count the correct number of digits.
  while (!isprint(i)){
    if (i==EOF){return;}
    else{i=fgetc(File);}}
  char CuName[STRING_SIZE];
  CuName[0]='\0';
  // Initalise the linked list variables.
  struct StringArr NameAr=StrArrInit;
  struct ByteArr ScoreAr=ByteArrInit;
  struct StringArr *LastName=&NameAr;
  struct ByteArr *LastScore=&ScoreAr;
  bool firstName=true;
  /*while i<len(FTXT):
        if"0"!=FTXT[i]and"1"!=FTXT[i]:*/ // python
  while (i!=EOF){
    if ('0'!=i && '1'!=i){
      if (j!=0 && j<5){fprintf(stderr,"ERROR: `j` exceeded 0 while parsing a name.\nMaybe the file is invalid?\n");}
      if (NameAr.Stri[0]!='\0'){firstName=false;}
      // If `i` isn't 0 or 1, append it to the end of `CuName`.
      char *end=strchr(CuName,'\0'); // Get a pointer for the end of `CuName`
      *end=i // Set it to `i`.
;     *(end+1)='\0'; // Put a NULL terminator at the next position.
    }

/*  else:
            if not CuName in NameAr:NameAr.append(CuName),ScoreAr.append([0,0])
            for j in range(5):
                if FTXT[i]=="1":ScoreAr[NameAr.index(CuName)][0]+=1
                else:ScoreAr[NameAr.index(CuName)][1]+=1
                i+=1
            CuName=""*/ // python
    else{
      unsigned int index=inStArr(&NameAr,CuName);
      if (!index){
        struct StringArr *newName=LastName;
        struct ByteArr *newScore=LastScore;
        if (!firstName){
          newName=(struct StringArr *)malloc(sizeof(struct StringArr));
          *newName=StrArrInit;
          newScore=(struct ByteArr *)malloc(sizeof(struct ByteArr));
          *newScore=ByteArrInit;
        }
        strcpy(newName->Stri,CuName);
        if (!firstName){
          LastName->next=newName;
          LastName=newName;
          LastScore->next=newScore;
          LastScore=newScore;}
        index=inStArr(&NameAr,CuName);
        if (!index){
          fprintf(stderr,"ERROR reading %s from file.\n",CuName);
          return;}}
      if (i=='1'){scoreFromIndex(&ScoreAr,index-1)->byte[0]++;}
      else if (i=='0'){scoreFromIndex(&ScoreAr,index-1)->byte[1]++;}
      else{
        fprintf(stderr,"ERROR reading file \"%s\".\nExpecting '0' or '1', but got '%c' instead.\n",file,i);
        return;}
      j++;
      if (j>5){fprintf(stderr,"ERROR: `j` exceeded 5.\n");}
      if (j==5){
        CuName[0]='\0';
        j=0;}}
    i=fgetc(File);}
  fclose(File);
    //for i in range(len(NameAr)):print(NameAr[i]+" got "+str(ScoreAr[i][0])+" correct and "+str(ScoreAr[i][1])+" wrong, which is "+str((ScoreAr[i][0]/(ScoreAr[i][0]+ScoreAr[i][1]))*100)+"% of questions correct.")
  struct StringArr *CuNameAr=&NameAr;
  struct ByteArr *CuScoreAr=&ScoreAr;
  while (CuNameAr!=NULL){
    if (CuNameAr==CuNameAr->next){
      fprintf(stderr,"ERROR: Linked list element linking itself. Infinate loop.\n");
      return;}
    //fprintf(stderr,"First character of name is %u. Full name is %s.\n",CuNameAr->Stri[0],CuNameAr->Stri); // Debug print.
    printf("%s got %u correct and %u wrong, which is %lf%% of questions correct.\n",CuNameAr->Stri,CuScoreAr->byte[0],CuScoreAr->byte[1],(CuScoreAr->byte[0]/(CuScoreAr->byte[0]+CuScoreAr->byte[1]+0.0))*100);
    struct StringArr *oldName=CuNameAr;
    struct ByteArr *oldScore=CuScoreAr;
    CuNameAr=CuNameAr->next;
    CuScoreAr=CuScoreAr->next;
    if (oldName!=&NameAr){
    free(oldName);
    free(oldScore);
    }}}

void SomeData(char file[STRING_SIZE]){
  // Similar to all data, but only needs to look through the data of one user.
  FILE *File;
  File=fopen(file,"r");
  if (!File){
    fprintf(stderr,"ERROR: File %s not found.\n",file);
    return;}
  // i,CuName,ReqName,ScoreAr=0,"",input("Who would you like to search for? "),[0,0] // python
  char ReqName[STRING_SIZE];
  printf("Who would you like to search for? ");
  if(fgets(ReqName,STRING_SIZE,stdin)==NULL)   {fprintf(stderr,"Error reading input.\n");ReqName[0]='\0';}
  while (sanitise(ReqName)){ // `sanitise` runs invalidName(Name) while fixing `Name`, so it can go directly in the if.
    printf("INVALID. Try again: ");
    if(fgets(ReqName,STRING_SIZE,stdin)==NULL)   {fprintf(stderr,"Error reading input.\n");ReqName[0]='\0';}
    printf("\n");}
  char i=fgetc(File); // `i` will be the current character being read from the file.
  unsigned char j=0; // `j` will count the correct number of digits.
  while (!isprint(i)){
    if (i==EOF){return;}
    else{i=fgetc(File);}}
  char CuName[STRING_SIZE];
  CuName[0]='\0';
  unsigned short right=0;
  unsigned short wrong=0;
  while (i!=EOF){
    if ('0'!=i && '1'!=i){
      if (j!=0 && j<5){fprintf(stderr,"ERROR: `j` exceeded 0 while parsing a name.\nMaybe the file is invalid?\n");}
      // If `i` isn't 0 or 1, append it to the end of `CuName`.
      char *end=strchr(CuName,'\0'); // Get a pointer for the end of `CuName`
      *end=i // Set it to `i`.
;     *(end+1)='\0';/*Put a NULL terminator at the next position.*/}

/*  else:
            if CuName==ReqName:
                for j in range(5):
                    if FTXT[i]=="1":ScoreAr[0]+=1
                    else:ScoreAr[1]+=1
                    i+=1
            else:i+=5*/ // python
    else{
      if (strcmp(ReqName,CuName)==0){
        if (i=='1'){right++;}
        else if (i=='0'){wrong++;}
      j++;
      if (j>5){fprintf(stderr,"ERROR: `j` exceeded 5.\n");}
      if (j==5){
        CuName[0]='\0';
        j=0;}}
      else{
        CuName[0]='\0';
        fseek(File, 4, SEEK_CUR);}
    }
  i=fgetc(File);}
  fclose(File);
  if(right+wrong){
    printf("%s got %u correct and %u wrong, which is %lf%% of questions correct.\n",ReqName,right,wrong,(right/(right+wrong+0.0))*100);
  }
  else{
    printf("%s not found. Be aware that this program is case/punctuation sensitive.\n",ReqName);
  }
}