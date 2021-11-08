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

graph_t *init_graph(size_t length)
{
   graph_t *graph     = (graph_t*)malloc(sizeof(graph_t));
   graph->nodes       = (node_t**)malloc(length * sizeof(node_t*));
   graph->len         = length;
   graph->index       = 0;
   graph->add_node    = add_node;
   graph->free        = free_graph;

   return graph;
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
   for(int i = 0; i <= (int)graph->len; ++i)
   {
     free(graph->nodes[i]);
   }

   free(graph->nodes);
   free(graph);
}

