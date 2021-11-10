#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdlib.h>
#include "../include/maze.h"

#define EDGES_COUNT 3

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
 node_t **nodes; 

 void (*load_maze) (struct graph*, struct maze*);
 void (*load_edges) (struct graph*, struct maze*);
 void (*free) (struct graph*);
}graph_t;

graph_t *init_graph(size_t length);

#endif



