#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct input
{
  int cursor;
  size_t len;
  size_t total_len;
  char *str;
} input_t;

typedef struct map
{
  int height;
  int width;
  char full;
  char empty;
  char path;
  char entrypoint;
  char exit;
  bool valid;
  input_t input;

  void (*load)(struct map*);

} map_t;


//map_t *load_map(char *str);

#endif
