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

static void load_header(map_t *map);
static void load_height(map_t *map);
static void load_width(map_t *map);
static void load_every(map_t *map);
static char next_char(map_t *map);
static bool validate(map_t *map);

static void read_file(map_t *map, char *file_path);
static int to_int(char *str);

map_t *init_map(char *file_path)
{
   map_t *map          = (map_t*)malloc(sizeof(map_t));
   map->load_header    = load_header;
   map->valid          = true;

   read_file(map, file_path);

   if(!map->valid)
      printf("Error loading file.");

   return map;
}


/* TODO: NEEDS WORK */
void load_header(map_t *map)
{

   if(!map->valid)
      return;

   map->input.cursor  = 0;
   load_height(map);
   load_width(map);
   load_every(map);
   
}

static void load_height(map_t *map)
{
   char buffer[map->input.header_len];

   while(map->input.data[map->input.cursor] != 'x')
   {

      if(!validate(map))
            return;

      buffer[map->input.cursor] = map->input.data[map->input.cursor];
      map->input.cursor++;

   }

   buffer[map->input.cursor] = '\0';
   map->height = to_int(buffer);

   /*  skip x  */
   map->input.cursor++;
}

static void load_width(map_t *map)
{
   if(!map->valid)
      return;

   char buffer[map->input.header_len];
   const int cursor = map->input.cursor;
   int i;

   for(i = 0; i <= (cursor / 2); ++i)
   {

      if(!validate(map))
            return;
      
      buffer[i] = map->input.data[map->input.cursor];
      map->input.cursor++;
   }

   buffer[++i] = '\0';
   map->width = to_int(buffer);
}

static void load_every(map_t *map)
{
   if(!map->valid)
      return;

   map->full = next_char(map);
   if(map->full == '\0' )
      return;

   map->empty = next_char(map);
   if(map->empty == '\0')
      return;

   map->path = next_char(map);
   if(map->path == '\0')
      return;

   map->entrypoint = next_char(map);
   if(map->entrypoint == '\0')
      return;

   map->exit = next_char(map);
   if(map->exit == '\0')
      return;

}

static void read_file(map_t *map, char *file_path)
{
   FILE *file;
   char *buffer;
   size_t result;

   if((file = fopen(file_path, "rb")) == NULL)
      {
      map->valid = false;
      return;
      }

   fseek(file, 0, SEEK_END);
   map->input.total_len = ftell(file);
   rewind(file);

   map->input.data = (char*)malloc((map->input.total_len + 1) * sizeof(char));

   if(fread(map->input.data, 1, map->input.total_len, file) != map->input.total_len)
       map->valid = false;

   map->input.data[map->input.total_len] = '\0';

   fclose(file);

}


static int to_int(char str[])
{
   char *ptr;
   return (int)strtol(str, &ptr, 10);
}


static bool validate(map_t *map)
{
   const char c = map->input.data[map->input.cursor];

   if(c < '0' || c > '9' || c == '\0')
   {
      map->valid = false;
      return false;
   }

   return true;
}

static char next_char(map_t *map)
{
   if(map->input.cursor >= (int)map->input.header_len) 
   {
      map->valid = false;
      return '\0';
   }

  return map->input.data[map->input.cursor++];
}

