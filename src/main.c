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

int main()
{

  map_t *map = init_map("20x20* o12");


  if(map != NULL)
  {

//  printf("h: %d, w: %d, full: %c, empty: %c, path: %c, ep: %c, exit: %c",
//     map->height, map->width, map->full, map->empty, map->path, map->entrypoint, map->exit);
    free(map);
  }

  
  return 0;
}
