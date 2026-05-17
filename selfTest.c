#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "structs.h"

bool invalidName(char Name[]);
unsigned int inStArr(struct StringArr *Arr, char i[]);

int selfTest(){
  int exit=0;
  if (!invalidName("")){
    fprintf(stderr,"ERROR: \"\" wrongly recognised as valid!\n");
    exit=1;}
  if (!invalidName("123abc")){
    fprintf(stderr,"ERROR: \"123abc\" wrongly recognised as valid!\n");
    exit=1;}
  if (invalidName("abc")){
    fprintf(stderr,"ERROR: \"abc\" wrongly recognised as invalid!\n");
    exit=1;}
  if (!invalidName("abc0123")){
    fprintf(stderr,"ERROR: \"abc0123\" wrongly recognised as valid!\n");
    exit=1;}
  struct StringArr testStrArr = {0};
  struct StringArr testStrArr2 = {0};
  struct StringArr testStrArr3 = {0};
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
  return 0;}