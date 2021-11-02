#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct input
{
  int cursor;
  size_t len;
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

} map_t;


map_t *init_map(char *str);

#endif
