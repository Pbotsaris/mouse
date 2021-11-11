#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdlib.h>
#include "../include/maze.h"

#define EDGES_COUNT 3
#define IS_NULL -1

typedef enum edges {NEXT, UNDER, DIAGONAL}edges_t;

typedef struct node{
  int value;
  char type;
  struct node *edges[EDGES_COUNT];
  struct node *parent;
  bool visited;

}node_t;

typedef struct graph{
 size_t len;
 int index;
 node_t *entrypoint;
 node_t *exit;
 node_t **nodes; 
 bool valid;

 void (*load_from_maze) (struct graph*, struct maze*);
 void (*load_edges) (struct graph*, struct maze*);
 void (*set_exit_entrypoint) (struct graph*, struct maze*);
 void (*free) (struct graph*);
}graph_t;

graph_t *init_graph(size_t length);

#endif



