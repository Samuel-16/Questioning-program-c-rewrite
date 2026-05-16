#ifndef CONSTANTS_H
#define CONSTANTS_H

#define STRING_SIZE 512

struct StringArr{
  char Stri[STRING_SIZE]/*=""*/; // STRING_SIZE
  struct StringArr* next/*=NULL*/;};

struct ByteArr{
  unsigned char byte[2]/*=(0,0)*/;
  struct ByteArr* next/*=NULL*/;};

static const struct StringArr StrArrInit={.Stri="",.next=NULL};
static const struct ByteArr ByteArrInit={.byte={0,0},.next=NULL};

#endif