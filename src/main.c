/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/02/2021 09:21:57
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include "../include/map.h"

  int main(int argc, char *argv[])
  {
    

//  map_t *map = load_map("20x20* o12");

  maze_t *maze = init_maze(argv[1]);

  printf("%s\n", maze->input.data);

  free(maze->input.data);
  free(maze);


//  if(map != NULL)
//  {
//
//  printf("h: %d, w: %d, full: %c, empty: %c, path: %c, ep: %c, exit: %c",
//     map->height, map->width, map->full, map->empty, map->path, map->entrypoint, map->exit);
//    free(map);
//  }
//
  
  return 0;
}
