/*
 * =====================================================================================
 *
 *       Filename:  maze.c
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
#include "../include/maze.h"


/*   PUBLIC  */
static void load_header(maze_t *maze);

/*  PRIVATE: load_header helpers  */
static void load_dimensions(maze_t *maze, fun_ptr load);
static void load_every(maze_t *maze);
static void load_height(maze_t *maze, char *buffer);
static void load_width(maze_t *maze, char *buffer);
static char next_char(maze_t *maze);
static bool validate(maze_t *maze);
static int to_int(char *str);

/*   PRIVATE: init_maze helpers  */
static void read_file(maze_t *maze, char *file_path);
static void count_header(maze_t *maze);


/*   PUBLIC FUNCTION  */

maze_t *init_maze(char *file_path)
{
   maze_t *maze         = (maze_t*)malloc(sizeof(maze_t));
   maze->load_header    = load_header;
   maze->valid          = true;
   maze->input.cursor   = 0;

   read_file(maze, file_path);
   count_header(maze);

   if(!maze->valid)
      printf("Error loading file.\n");

   return maze;
}

/*   PUBLIC METHOD  */

void load_header(maze_t *maze)
{
   if(!maze->valid)
      return;

   load_dimensions(maze, load_height);
   maze->input.cursor++;
   load_dimensions(maze, load_width);
   load_every(maze);

   /* cursor to the first char of data */
   maze->input.cursor++;

   if(!maze->valid)
      printf("MAP ERROR: Bad header format.\n");

   if(maze->height > 1000 || maze->width > 1000)
   {
      maze->valid = false;
      printf("MAP ERROR: Max map length exceded.\n");
   }
}

/*   INIT_MAZE HELPERS  */

static void read_file(maze_t *maze, char *file_path)
{
   FILE *file;

   if((file = fopen(file_path, "rb")) == NULL)
   {
      maze->valid = false;
      return;
   }

   fseek(file, 0, SEEK_END);
   maze->input.total_len = ftell(file);
   rewind(file);

   maze->input.data = (char*)malloc((maze->input.total_len + 1) * sizeof(char));

   if(fread(maze->input.data, 1, maze->input.total_len, file) != maze->input.total_len)
      maze->valid = false;

   fclose(file);

}

static void count_header(maze_t *maze)
{
   if(!maze->valid)
      return;

   maze->input.data[maze->input.total_len] = '\0';

   maze->input.header_len = 0;

   while(maze->input.data[maze->input.header_len] != '\n')
      maze->input.header_len++;
}

/*    LOAD_HEADER HELPERS  */

static void load_dimensions(maze_t *maze, fun_ptr load)
{

   if(!maze->valid)
      return;

   int index = 0;

   char buffer[maze->input.header_len];

   while(maze->input.data[maze->input.cursor] >= '0' && maze->input.data[maze->input.cursor] <= '9')
   {

      if(!validate(maze))
         return;

      buffer[index] = maze->input.data[maze->input.cursor];
      maze->input.cursor++;
      index++;

   }
   buffer[index] = '\0';

   load(maze, buffer);
}

static void load_every(maze_t *maze)
{
   if(!maze->valid)
      return;

   maze->full = next_char(maze);
   if(maze->full == '\0' )
      return;

   maze->empty = next_char(maze);
   if(maze->empty == '\0')
      return;

   maze->path = next_char(maze);
   if(maze->path == '\0')
      return;

   maze->entrypoint = next_char(maze);
   if(maze->entrypoint == '\0')
      return;

   maze->exit = next_char(maze);
   if(maze->exit == '\0')
      return;
}

static void load_height(maze_t *maze, char *buffer) { maze->height = to_int(buffer); }
static void load_width(maze_t *maze, char *buffer) { maze->width = to_int(buffer); }


static int to_int(char str[])
{
   char *ptr;
   return (int)strtol(str, &ptr, 10);
}

static bool validate(maze_t *maze)
{
   const char c = maze->input.data[maze->input.cursor];

   if(c < '0' || c > '9' || c == '\0')
   {
      maze->valid = false;
      return false;
   }

   return true;
}

static char next_char(maze_t *maze)
{
   if(maze->input.cursor >= (int)maze->input.header_len) 
   {
      maze->valid = false;
      return '\0';
   }

   return maze->input.data[maze->input.cursor++];
}



