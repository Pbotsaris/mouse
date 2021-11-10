/*
 * =====================================================================================
 *
 *       Filename:  graph.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/03/2021 10:31:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdlib.h>

#include "../include/graph.h"

static void add_node(graph_t *graph, int value);
static void free_graph(graph_t *graph);
static void load_maze(graph_t *graph, maze_t *maze);
static void load_edges(graph_t *graph, maze_t *maze);
static void add_edges(graph_t *graph, int next, int under, int diagonal);

graph_t *init_graph(size_t length)
{
   graph_t *graph     = (graph_t*)malloc(sizeof(graph_t));
   graph->nodes       = (node_t**)malloc((length + 1)  * sizeof(node_t*));
   graph->len         = length;
   graph->index       = 0;
   graph->load_maze   = load_maze;
   graph->free        = free_graph;
   graph->load_edges  = load_edges;

   return graph;
}

static void load_maze(graph_t *graph, maze_t *maze)
{
   while(maze->input.data[maze->input.cursor] != '\0')
   {
      if( maze->input.data[maze->input.cursor] != '\n')
         add_node(graph, maze->input.data[maze->input.cursor]);
      maze->input.cursor++;
   }
    
      /* dealloc input mem */
      free(maze->input.data);
} 

static void load_edges(graph_t *graph, maze_t *maze)
{
   graph->index      = 0;
   int column        = 0;
   int row           = 0;

   while(graph->index < (int)graph->len)
   {

      int next       =  graph->index + 1;
      int under      =  graph->index + maze->width; // +1 to skip \n
      int diagonal   =  graph->index + maze->width + 1; 

      if(column == maze->width - 1 && row == maze->height - 1)
         add_edges(graph, -1, -1, -1);
      else if(row == maze->height - 1)
         add_edges(graph, next, -1, -1);

      else if(column == maze->width - 1)
         add_edges(graph, -1, under, -1);
      else
         add_edges(graph, next, under, diagonal);

      graph->index++;
      if(column <  maze->width - 1)
         column++;
      else
      {
         column = 0;
         row++;
      }
   }
}


static void add_edges(graph_t *graph, int next, int under, int diagonal)
{

   if(next >= 0)
      graph->nodes[graph->index]->edges[NEXT] = graph->nodes[next];
   else
      graph->nodes[graph->index]->edges[NEXT] = NULL;

   if(under >= 0)
      graph->nodes[graph->index]->edges[UNDER] = graph->nodes[under];
   else
      graph->nodes[graph->index]->edges[UNDER] = NULL;

   if(diagonal >= 0)
      graph->nodes[graph->index]->edges[DIAGONAL] = graph->nodes[diagonal];
   else
      graph->nodes[graph->index]->edges[DIAGONAL] = NULL;
}

static void add_node(graph_t *graph, int value)
{
   node_t *node = (node_t*)malloc(sizeof(node_t));
   node->value = value;
   node->visited = false;

   graph->nodes[graph->index] = node;
   graph->index++;

}


static void free_graph(graph_t *graph)
{
   printf("index: %d\n", graph->index);
   for(size_t i = 0; i < graph->len; ++i)
   {
      free(graph->nodes[i]);
   }

   free(graph->nodes);
   free(graph);
}

