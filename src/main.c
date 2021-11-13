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

  maze_t *maze = init_maze(argv[1]);
  maze->load_header(maze);

  if(maze->valid)
  {
    graph_t *graph = init_graph(maze->height * maze->width);
    graph->load_from_maze(graph, maze);
    graph->load_edges(graph, maze);
    graph->set_exit_entrypoint(graph, maze);

    graph->search_path(graph);
    graph->write_path(graph, maze);
    if(graph->valid)
        graph->print(graph, maze);

    graph->free(graph);
  }
  else
    free(maze->input.data);

  free(maze);


  return 0;
}

