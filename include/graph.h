#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdlib.h>

#define EDGES_COUNT 3

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

 void (*add_node) (struct graph*, int);
 void (*free) (struct graph*);
}graph_t;

graph_t *init_graph(size_t length);

#endif



