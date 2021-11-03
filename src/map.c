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

static void load_height(map_t *map, input_t *input);
static void load_width(map_t *map, input_t *input);
static void load_every(map_t *map, input_t *input);
static char next_char(map_t *map, input_t *input);

static int to_int(char *str);
static bool validate(map_t *map, input_t *input);

// 
map_t *init_map(char *str)
{
   input_t input;
   input.len      = strlen(str);
   input.str      = (char*)malloc((input.len + 1) *sizeof(char));
   map_t *map     = (map_t*)malloc(sizeof(map_t));
   map->valid     = true;
   input.cursor   = 0;

   strncpy(input.str, str, input.len);
   load_height(map, &input);
   load_width(map, &input);
   load_every(map, &input);

   if(!map->valid)
   {
      printf("Bad input\n");
      free(map);
      return NULL;
   }
   
   return map;
}

static void load_height(map_t *map , input_t *input)
{
   char buffer[input->len];

   while(input->str[input->cursor] != 'x')
   {

      if(!validate(map, input))
            return;

      buffer[input->cursor] = input->str[input->cursor];
      input->cursor++;

   }

   buffer[input->cursor] = '\0';
   map->height = to_int(buffer);

   /*  skip x  */
   input->cursor++;
}

static void load_width(map_t *map, input_t *input)
{
   if(!map->valid)
      return;

   char buffer[input->len];
   const int cursor = input->cursor;
   int i;

   for(i = 0; i <= (cursor / 2); ++i)
   {
      if(!validate(map, input))
            return;
      
      buffer[i] = input->str[input->cursor];
      input->cursor++;
   }

   buffer[++i] = '\0';
   map->width = to_int(buffer);
}

static void load_every(map_t *map, input_t *input)
{
   if(!map->valid)
      return;

   map->full = next_char(map, input);
   if(map->full == '\0' )
      return;

   map->empty = next_char(map,input);
   if(map->empty == '\0')
      return;

   map->path = next_char(map,input);
   if(map->path == '\0')
      return;

   map->entrypoint = next_char(map,input);
   if(map->entrypoint == '\0')
      return;

   map->exit = next_char(map, input);
   if(map->exit == '\0')
      return;

}


static int to_int(char str[])
{
   char *ptr;
   return (int)strtol(str, &ptr, 10);
}


static bool validate(map_t *map, input_t *input)
{
   const char c = input->str[input->cursor];

   if(c < '0' || c > '9' || c == '\0')
   {
      map->valid = false;
      return false;
   }

   return true;
}

static char next_char(map_t *map, input_t *input)
{
   if(input->cursor >= (int)input->len) 
   {
      map->valid = false;
      return '\0';
   }

  return input->str[input->cursor++];
}

