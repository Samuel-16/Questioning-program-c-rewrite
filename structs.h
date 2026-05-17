#ifndef STRING_SIZE
#define STRING_SIZE 512

struct StringArr{
  char Stri[STRING_SIZE]/*=""*/; // STRING_SIZE
  struct StringArr* next/*=NULL*/;};

struct ByteArr{
  unsigned char byte[2]/*=(0,0)*/;
  struct ByteArr* next/*=NULL*/;};

#endif