#ifndef MEMO_H
#define MEMO_H

#include <stdlib.h>

typedef struct memo{
  char *store;
  int index;
  int prev;
  int row;
  int pos[2];
  int max;

  }memo_t;


#endif
