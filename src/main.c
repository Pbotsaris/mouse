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
 >?*       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include "../include/maze.h"
#include "../include/graph.h"

int main(int argc, char *argv[])
{

  //  map_t *map = load_map("20x20* o12");

  maze_t *maze = init_maze(argv[1]);
  maze->load_header(maze);

  printf("%s\n", maze->input.data);

  printf("h: %d, w: %d, full: %c, empty: %c, path: %c, ep: %c, exit: %c, cursor: %d\n",
      maze->height, maze->width, maze->full, maze->empty, maze->path, maze->entrypoint, maze->exit, maze->input.cursor);

  if(maze->valid)
  {
    graph_t *graph = init_graph(maze->height * maze->width);
    graph->load_maze(graph, maze);
    graph->load_edges(graph, maze);
    graph->free(graph);
  }
  else
     free(maze->input.data);

  //  node_t *node = graph->nodes[7];
  // printf("node: %c, next: %c, under: %c, diagonal: %c \n", node->value, node->edges[NEXT]->value, node->edges[UNDER]->value, node->edges[DIAGONAL]->value);

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

// r
