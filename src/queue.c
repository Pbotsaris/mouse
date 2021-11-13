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

static void enqueue(queue_t *queue, node_t *node);
static node_t *dequeue(queue_t *queue);
static bool contains(queue_t *queue, node_t *node);
static bool is_empty(queue_t *queue);


queue_t *init_queue()
{
  queue_t *queue       = (queue_t*)malloc(sizeof(queue_t));
  queue->rear          = NULL;
  queue->front         = NULL;
  queue->enqueue       = enqueue;
  queue->dequeue       = dequeue;
  queue->contains      = contains;
  queue->is_empty      = is_empty;

  return queue;
}


static void enqueue(queue_t *queue, node_t *node)
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

static node_t *dequeue(queue_t *queue)
{

  if(queue->front == NULL)
    return NULL;

  if(queue->front->next_in_queue == NULL)
    queue->rear = NULL;

  node_t *node = queue->front;
  queue->front = node->next_in_queue;

  return node;

}

static bool is_empty(queue_t *queue)
{
  if(queue->front || queue->rear)
    return false;

  return true;

}

static bool contains(queue_t *queue, node_t *node)
{
  node_t *temp = queue->front;

  while(temp)
  {
    if(node == temp)
      return true;

    temp = temp->next_in_queue;
  }

  return false;
}
