#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

const short unsigned int STRING_SIZE=512;

struct StringArr{
  char Stri[512]/*=""*/; // STRING_SIZE
  struct StringArr* next/*=NULL*/;};

struct ByteArr{
  unsigned char byte[2]/*=(0,0)*/;
  struct ByteArr* next/*=NULL*/;};

const struct StringArr StrArrInit={.Stri="",.next=NULL};
const struct ByteArr ByteArrInit={.byte={0,0},.next=NULL};

int DEZERO(int x){
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

int sanitise(char stri[]){
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
  /*Name=input("What is your name: ")
    while"0"in Name or"1"in Name or Name=="":Name=input("INVALID. Try again: ")
    File.write(Name)*/
  getchar(); // Clean the input stream.
  char Name[STRING_SIZE];
  printf("What is your name: ");
  fgets(Name,STRING_SIZE,stdin);
  printf("\n");
  //sanitise(Name);
  while (sanitise(Name)){ // `sanitise` runs invalidName(Name) while fixing `Name`, so it can go directly in the if.
    printf("INVALID. Try again: ");
    fgets(Name,STRING_SIZE,stdin);
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
    unsigned short int Guess;
    scanf("%hu", &Guess);
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
  /*while i<len(FTXT):
        if"0"!=FTXT[i]and"1"!=FTXT[i]:*/ // python
  while (i!=EOF){
    //printf("%u",i); // debug print
    if ('0'!=i && '1'!=i){
      // If `i` isn't 0 or 1, append it to the end of `CuName`.
      char *end=strchr(CuName,'\0'); // Get a pointer for the end of `CuName`
      *end=i // Set it to `i`.
;     *(end+1)='\0';/*Put a NULL terminator at the next position.*/}
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
        struct StringArr newName=StrArrInit;
        strcpy(newName.Stri,CuName);
        LastName->next=&newName;
        LastName=&newName;
        struct ByteArr newScore=ByteArrInit;
        LastScore->next=&newScore;
        LastScore=&newScore;
        index=inStArr(&NameAr,CuName);
        if (!index){
          fprintf(stderr,"ERROR reading %s from file.\n",CuName);
          return;}}
      if (i=='1'){scoreFromIndex(&ScoreAr,index)->byte[0]++;}
      else if (i=='0'){scoreFromIndex(&ScoreAr,index)->byte[1]++;}
      else{
        fprintf(stderr,"ERROR reading file \"%s\".\nExpecting '0' or '1', but got '%c' instead.\n",file,i);
        return;}
    CuName[0]='\0';}
    i=fgetc(File);}
  fclose(File);
    //for i in range(len(NameAr)):print(NameAr[i]+" got "+str(ScoreAr[i][0])+" correct and "+str(ScoreAr[i][1])+" wrong, which is "+str((ScoreAr[i][0]/(ScoreAr[i][0]+ScoreAr[i][1]))*100)+"% of questions correct.")
  struct StringArr *CuNameAr=NameAr.next;
  struct ByteArr *CuScoreAr=ScoreAr.next;
  while (CuNameAr!=NULL){
    if (CuNameAr==CuNameAr->next){
      fprintf(stderr,"ERROR: Linked list element linking itself. Infinate loop.\n");
      return;}
    //fprintf(stderr,"First character of name is %u. Full name is %s.\n",CuNameAr->Stri[0],CuNameAr->Stri); // Debug print.
    printf("%s got %u correct and %u wrong, which is %lf%% of questions correct.\n",CuNameAr->Stri,CuScoreAr->byte[0],CuScoreAr->byte[1],(CuScoreAr->byte[0]/(CuScoreAr->byte[0]+CuScoreAr->byte[1]+0.0))*100);
    CuNameAr=CuNameAr->next;
    CuScoreAr=CuScoreAr->next;
    }}
    
int selfTest(){
  int exit=0;
  if (!invalidName("")){
    fprintf(stderr,"ERROR: \"\" wrongly recognised as valid!");
    exit=1;}
  if (!invalidName("123abc")){
    fprintf(stderr,"ERROR: \"123abc\" wrongly recognised as valid!");
    exit=1;}
  if (invalidName("abc")){
    fprintf(stderr,"ERROR: \"abc\" wrongly recognised as invalid!");
    exit=1;}
  if (!invalidName("abc0123")){
    fprintf(stderr,"ERROR: \"abc0123\" wrongly recognised as valid!");
    exit=1;}
  struct StringArr testStrArr = StrArrInit;
  struct StringArr testStrArr2 = StrArrInit;
  struct StringArr testStrArr3 = StrArrInit;
  strcpy(testStrArr.Stri,"Bob");
  strcpy(testStrArr2.Stri,"May");
  strcpy(testStrArr3.Stri,"Keri");
  testStrArr.next=&testStrArr2;
  testStrArr2.next=&testStrArr3;
  unsigned int undecIndex;
  undecIndex=inStArr(&testStrArr,"Bob");
  if (undecIndex!=1){
    fprintf(stderr,"ERROR: \"Bob\" wrongly found at %u instead of 1 in test linked list [\"Bob\",\"May\",\"Keri\"]!\n",undecIndex);
    exit=1;}
  undecIndex=inStArr(&testStrArr,"May");
  if (undecIndex!=2){
    fprintf(stderr,"ERROR: \"May\" wrongly found at %u instead of 2 in test linked list [\"Bob\",\"May\",\"Keri\"]!\n",undecIndex);
    exit=1;}
  undecIndex=inStArr(&testStrArr,"Keri");
  if (undecIndex!=3){
    fprintf(stderr,"ERROR: \"Keri\" wrongly found at %u instead of 3 in test linked list [\"Bob\",\"May\",\"Keri\"]!\n",undecIndex);
    exit=1;}
  undecIndex=inStArr(&testStrArr,"Yolk");
  if (undecIndex!=0){
    fprintf(stderr,"ERROR: \"Yolk\" wrongly found at %u instead of 0 in test linked list [\"Bob\",\"May\",\"Keri\"]!\n",undecIndex);
    exit=1;}
  if (testStrArr3.next!=NULL){
    fprintf(stderr,"ERROR: Linked list does not end in NULL pointer.\n");
    exit=1;}
  return exit;}
  
int main(int argc, char *argv[]){
  assert(!selfTest());
  // <Setting things up>
  char Command;
  char file[STRING_SIZE];
  strcpy(file,"RESULTS");
  srand(time(NULL));  // seed with current time
  //while 1:Menu(Func=[Addition,AllData,SomeData,quit,ChangeFile],Arg=[file,file,file],INP="Enter: 0 to take the test, 1 to view all scores, 2 to view specific scores, 3 to quit, or 4 to change the source file")
  while (true){
    printf("Enter: 0 to take the test, 1 to view all scores, 2 to view specific scores, 3 to quit, or 4 to change the source file: ")
;   scanf("%c", &Command)
//;   printf("\n")
;   switch (Command){
      case '0':
        Addition(file);
        break;
      case '1':
        AllData(file);
        break;
      case '2':
        break;
      case '3':
        return 0;
        break;
      case '4':
        break;}
    };}


