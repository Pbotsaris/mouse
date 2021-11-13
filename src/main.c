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
    graph->load_from_maze(graph, maze);
    graph->load_edges(graph, maze);
    graph->set_exit_entrypoint(graph, maze);

    graph->search_path(graph);

//    graph->queue->enqueue(graph->queue, graph->nodes[5]);
//    graph->queue->enqueue(graph->queue, graph->nodes[13]);
//    graph->queue->enqueue(graph->queue, graph->nodes[1]);


    //
//    node_t *node = graph->queue->dequeue(graph->queue);
//    //  printf("node infront: %c\n", node->value);
//    node = graph->queue->dequeue(graph->queue);
//    //  printf("node next: %c\n", node->value);
//    //
//    if(graph->queue->is_empty(graph->queue))
//      printf("is empty\n");
//    else
//      printf("not empty\n");
//
//    node = graph->queue->dequeue(graph->queue);
//    //   printf("node last: %c\n", node->value);
//    if(graph->queue->is_empty(graph->queue))
//      printf("is empty\n");
//    else
//      printf("not empty\n");
//
    //
    //    printf("entry = %c exit = %c", graph->entrypoint->value, graph->exit->value);
    //

    //    node_t *node = graph->nodes[12];
    //
    //    printf("node: %c, next: %c, prev:%c under: %c, over: %c \n", node->value, node->edges[NEXT]->value, node->edges[PREV]->value, node->edges[UNDER]->value, node->edges[OVER]->value);
    //


//    free(graph->queue);
    graph->free(graph);
  }
  else
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

// r
