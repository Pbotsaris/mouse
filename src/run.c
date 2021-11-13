/*
 * =====================================================================================
 *
 *       Filename:  run.c
 *
 *    Description:   
 *
 *        Version:  1.0
 *        Created:  11/13/21 10:45:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Pedro Botsaris
 *   Organization:  
 *
 * =====================================================================================
 */


#include "../include/run.h"

static void search(maze_t *maze);

void run(int argc, char *argv[])
{

  if(argc < 2)
  {
    printf("Must provide file path as first argument\n");
    return;
  }

  maze_t *maze = init_maze(argv[1]);
  maze->load_header(maze);

  search(maze);
  free(maze);
}


static void search(maze_t *maze)
{
  if(maze->valid)
  {
    graph_t *graph = init_graph(maze->height * maze->width);
    graph->load_from_maze(graph, maze);
    graph->load_edges(graph, maze);
    graph->set_exit_entrypoint(graph, maze);

    graph->search_path(graph);
   int steps = graph->write_path(graph, maze);

    if(graph->valid)
    {
        graph->print(graph, maze);
        printf("%d Steps!\n", steps);
    }
    else
      printf("Did not find a valid path\n");

    graph->free(graph);
  }
  else
    free(maze->input.data);
}

