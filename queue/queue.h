#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>

#define queue_for_each(queue, node) \
    for (node = (queue)->head; (node) != NULL; node = (node)->next)

#define queue_reverse_for_each(queue, node) \
    for (node = (queue)->tail; (node) != NULL; node = (node)->pre)

#define queue_is_empty(queue) \
    (((queue)->head == NULL) && ((queue)->tail == NULL))


typedef struct node Node;
struct node {
    Node *pre;
    Node *next;
    void *data;
};

typedef struct queue {
    Node *head;
    Node *tail;
} Queue;

void queue_init(Queue *queue);

void queue_insert_head (Queue *queue, Node *node);

void queue_insert_tail (Queue *queue, Node *node);

Node *queue_get_head (Queue *queue);

Node *queue_get_tail (Queue *queue);

#endif /* !QUEUE_H */
