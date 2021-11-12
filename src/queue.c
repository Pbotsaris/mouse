/*
 * =====================================================================================
 *
 *       Filename:  queue.c
 *
 *    Description:   
 *
 *        Version:  1.0
 *        Created:  11/11/21 23:31:12
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */


#include "../include/graph.h"

void enqueue(queue_t *queue, node_t *node);
node_t *dequeue(queue_t *queue);


queue_t *init_queue()
{
  queue_t *queue       = (queue_t*)malloc(sizeof(queue_t));
  queue->rear          = NULL;
  queue->front         = NULL;
  queue->enqueue       = enqueue;
  queue->dequeue       = dequeue;

  return queue;
}


void enqueue(queue_t *queue, node_t *node)
{
  node->next_in_queue = NULL;

  if(queue->rear == NULL && queue->front == NULL)
  {
    queue->rear = queue->front = node;
    return;
  }

  queue->rear->next_in_queue = node;
  queue->rear = node;

}

node_t *dequeue(queue_t *queue)
{

  if(queue->front == NULL)
    return NULL;


  node_t *node = queue->front;
  queue->front = node->next_in_queue;

  return node;

}
