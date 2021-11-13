#ifndef MAZE_H
#define MAZE_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct input
{
  int cursor;
  size_t header_len;
  size_t total_len;
  char *data;
} input_t;

typedef struct maze
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

  void (*load_header)(struct maze*);

} maze_t;

typedef void (*fun_ptr)(maze_t*, char*);

//map_t *load_map(char *str);

maze_t *init_maze(char *file_path);

#endif
