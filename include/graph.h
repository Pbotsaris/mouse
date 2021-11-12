#ifndef GRAPH_H
#define GRAPH_H

#include <stdbool.h>
#include <stdlib.h>
#include "../include/maze.h"
#include "../include/queue.h"

#define EDGES_COUNT 4
#define IS_NULL -1

typedef enum edges {NEXT, PREV, UNDER, OVER}edges_t;

typedef struct node{
  int value;
  char type;
  struct node *edges[EDGES_COUNT];
  struct node *parent;
  struct node *next_in_queue;
  bool visited;

}node_t;


typedef struct queue{
  node_t *front;
  node_t * rear;

void (*enqueue) (struct queue*, node_t*);
node_t* (*dequeue) (struct queue*);

}queue_t; 


typedef struct graph{
 size_t len;
 int index;
 node_t *entrypoint;
 node_t *exit;
 node_t **nodes; 
 queue_t *queue;
 bool valid;

 void (*load_from_maze) (struct graph*, struct maze*);
 void (*load_edges) (struct graph*, struct maze*);
 void (*set_exit_entrypoint) (struct graph*, struct maze*);
 void (*free) (struct graph*);
}graph_t;

graph_t *init_graph(size_t length);
queue_t *init_queue();

#endif



