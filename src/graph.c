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

/* PUBLIC METHODS */
static void load_from_maze(graph_t *graph, maze_t *maze);
static void load_edges(graph_t *graph, maze_t *maze);
static void set_exit_entrypoint(graph_t *graph, maze_t *maze);
static int write_path(graph_t *graph, maze_t *maze);
static void print(graph_t *graph, maze_t *maze);
static void free_graph(graph_t *graph);
static void search_path(graph_t *graph);

/* PRIVATE */
static void add_edges(graph_t *graph, int next, int prev,  int under, int over);
static void add_node(graph_t *graph, maze_t *maze);
static void set_entrypoint(graph_t *graph, maze_t *maze);
static void set_exit(graph_t *graph, maze_t *maze);

/*  PUBLIC FUNCTIONS */
graph_t *init_graph(size_t length)
{
   graph_t *graph              = (graph_t*)malloc(sizeof(graph_t));
   graph->nodes                = (node_t**)malloc((length + 1)  * sizeof(node_t*));
   graph->len                  = length;
   graph->index                = 0;
   graph->valid                = true;
   graph->load_from_maze       = load_from_maze;
   graph->free                 = free_graph;
   graph->load_edges           = load_edges;
   graph->set_exit_entrypoint  = set_exit_entrypoint;
   graph->search_path          = search_path;
   graph->write_path           = write_path;
   graph->print                = print;

   return graph;
}

/*  PUBLIC METHODS */

static void load_from_maze(graph_t *graph, maze_t *maze)
{
   while(maze->input.data[maze->input.cursor] != '\0')
   {
      if( maze->input.data[maze->input.cursor] != '\n')
         add_node(graph, maze);

      maze->input.cursor++;
   }

   /* input data is not needed from this point on */
   free(maze->input.data);
} 

 /*     o
 **    pxn    n = next       p = previous      x = current
 **     u     u = under      d = diagonal
 */
static void load_edges(graph_t *graph, maze_t *maze)
{
   graph->index           = 0;
   int column             = 0;
   int row                = 0;

   while(graph->index < (int)graph->len)
   {
      int next            =  graph->index + 1;
      int prev            =  graph->index - 1;
      int under           =  graph->index + maze->width; 
      int over            =  graph->index - maze->width;


      /*  first row & col  */
       if(column == 0 && row == 0)
         add_edges(graph, next, IS_NULL, under , IS_NULL);

      /*  last row & col  */
      else if(column == maze->width - 1 && row == maze->height - 1)
         add_edges(graph, IS_NULL, prev,  IS_NULL, over);

      /*  first col  */
      else if(column == 0)
            add_edges(graph, next, IS_NULL, under, over);

      /*  first row  */
       else if(row == 0)
            add_edges(graph, next, prev, under, IS_NULL);

      /*  last  row  */
      else if(row == maze->height - 1)
      {
         if(column == 0)
            add_edges(graph, next, IS_NULL, IS_NULL, over);
         else
            add_edges(graph, next, prev, IS_NULL, over);
      }

      /*  last  col  */
      else if(column == maze->width - 1)
      {
         if(row == 0)
            add_edges(graph, IS_NULL, prev, under, IS_NULL);
         else  
            add_edges(graph, IS_NULL, prev, under, over);
      }

      /*  rest  */
      else
         add_edges(graph, next, prev, under, over);

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


static void set_exit_entrypoint(graph_t *graph, maze_t *maze)
{
   set_entrypoint(graph, maze);
   set_exit(graph, maze);

}


static int write_path(graph_t *graph, maze_t *maze)
{
   node_t *next = graph->exit->parent;
   int count    = 0;

   if(next == NULL)
   {
      graph->valid = false;
      return 0;
   }

   while(next != graph->entrypoint)
   {
      if(next == NULL)
      {
         graph->valid = false;
         return 0;
      }

      next->value = maze->path;
      next = next->parent;
      count++;
   }


   return count;

}

static void print(graph_t *graph, maze_t *maze)
{
   int column = 0;

   for(size_t i = 0; i < graph->len; i++)
   { 
      printf("%c", graph->nodes[i]->value);

      if(column <  maze->width - 1)
         column++;
      else
      {
         printf("\n");
         column = 0;
      }
    }
}


static void search_path(graph_t *graph)
{
   queue_t *queue              = init_queue();
   graph->entrypoint->visited  = true;

   queue->enqueue(queue, graph->entrypoint);

   while(!queue->is_empty(queue))
   {
      node_t *current = queue->dequeue(queue);

      if(current == graph->exit)
         break;

      for(int i = 0; i < EDGES_COUNT; i++)
      {
         node_t * neighbor = current->edges[i];

         if( neighbor != NULL && !neighbor->visited)
         {
            neighbor->visited = true;
            neighbor->parent = current;
            if(neighbor->type == EMPTY || neighbor->type == IO)
               queue->enqueue(queue, neighbor);
         }
      }
   }

   free(queue);
}


static void free_graph(graph_t *graph)
{
   for(size_t i = 0; i < graph->len; ++i)
   {
      free(graph->nodes[i]);
   }

   free(graph->nodes);
   free(graph);
}


/*  PRIVATE */

static void add_edges(graph_t *graph, int next, int prev, int under, int over)
{

   if(next >= 0)
      graph->nodes[graph->index]->edges[NEXT] = graph->nodes[next];
   else
      graph->nodes[graph->index]->edges[NEXT] = NULL;

   if(prev >= 0)
      graph->nodes[graph->index]->edges[PREV] = graph->nodes[prev];
   else
      graph->nodes[graph->index]->edges[PREV] = NULL;

   if(under >= 0)
      graph->nodes[graph->index]->edges[UNDER] = graph->nodes[under];
   else
      graph->nodes[graph->index]->edges[UNDER] = NULL;

   if(over >= 0)
      graph->nodes[graph->index]->edges[OVER] = graph->nodes[over];
   else
      graph->nodes[graph->index]->edges[OVER] = NULL;
}


static void add_node(graph_t *graph, maze_t *maze)
{
   node_t *node = (node_t*)malloc(sizeof(node_t));
   node->value = maze->input.data[maze->input.cursor];
   node->visited = false;
   node->parent = NULL;

   if(node->value == maze->full)
      node->type = FULL;
   else if(node->value == maze->empty)
      node->type = EMPTY;
   else
      node->type = IO;

   graph->nodes[graph->index] = node;
   graph->index++;

}


static void set_entrypoint(graph_t *graph, maze_t *maze)
{

   for(int i = 0; i < maze->width; i++)
   {
      if(graph->nodes[i]->value == maze->entrypoint)
      {
         graph->entrypoint = graph->nodes[i];
         return;
      }
   }

   printf("Maze does not contain an entry point\n");
   graph->valid = false;

}


static void set_exit(graph_t *graph, maze_t *maze)
{
   int end = maze->width * maze->height;

   for(int i = end - maze->width; i < end; i++)
   {
      if(graph->nodes[i]->value == maze->exit)
      {
         graph->exit = graph->nodes[i];
         return;
      }
   }

   printf("Maze does not contain an exit point\n");
   graph->valid = false;

}

