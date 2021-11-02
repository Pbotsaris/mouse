/*
 * =====================================================================================
 *
 *       Filename:  map.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/02/2021 09:55:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "../include/map.h"

// 

static int load_height(map_t *map, input_t *input);
static int load_width(map_t *map, input_t *input);
static int load_every(map_t *map, input_t *input);
static char next_char(input_t *input);
static int to_int(char *str);
static int validate(input_t *input);

// 
map_t *init_map(char *str)
{
   input_t input;
   input.len      = strlen(str);
   input.str      = (char*)malloc((input.len + 1) *sizeof(char));
   map_t *map     = (map_t*)malloc(sizeof(map_t));
   input.cursor   = 0;

   strncpy(input.str, str, input.len);
   load_height(map, &input);
   load_width(map, &input);

   if(!load_every(map, &input))
   {
       printf("bad input\n");
        return NULL;
   }
   
      printf("h: %d, w: %d, full: %c, empty: %c, path: %c, entrypoint: %c, exit: %c ", map->height, map->width, map->full, map->empty, map->path, map->entrypoint, map->exit);

   return map;
}

static int load_height(map_t *map , input_t *input)
{
   char buffer[input->len];

   while(input->str[input->cursor] != 'x')
   {

      if(validate(input))
            return 0;

      buffer[input->cursor] = input->str[input->cursor];
      input->cursor++;

   }

   buffer[input->cursor] = '\0';
   map->height = to_int(buffer);

   /*  skip x  */
   input->cursor++;

   return 1;
}

static int load_width(map_t *map, input_t *input)
{

   char buffer[input->len];
   const int cursor = input->cursor;
   int i;

   for(i = 0; i <= (cursor / 2); ++i)
   {
      if(validate(input))
            return 0;
      
      buffer[i] = input->str[input->cursor];
      input->cursor++;
   }

   buffer[++i] = '\0';
   map->width = to_int(buffer);

   return 1;

}

static int load_every(map_t *map, input_t *input)
{

   map->full = next_char(input);

   if(map->full == '\0' )
      return 0;

   map->empty = next_char(input);

   if(map->empty == '\0')
      return 0;

   map->path = next_char(input);

   if(map->path == '\0')
      return 0;

   map->entrypoint = next_char(input);

   if(map->entrypoint == '\0')
      return 0;

   map->exit = next_char(input);

   if(map->exit == '\0')
      return 0;

   return 1;
}


static int to_int(char str[])
{
   char *ptr;
   return (int)strtol(str, &ptr, 10);
}


static int validate(input_t *input)
{
   const char c = input->str[input->cursor];

   if(c < '0' || c > '9' || c == '\0')
   {
      printf("Bad input\n");
      return 1;
   }

   return 0;
}

static char next_char(input_t *input)
{
   if(input->cursor >= (int)input->len) 
      return '\0';

  return input->str[input->cursor++];
}

