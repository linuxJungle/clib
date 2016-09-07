#ifndef QUEUE_H
#define QUEUE_H

#include <pthread.h>

#define queue_for_each(queue, node) \
    for (node = (queue)->head; (node) != NULL; node = (node)->next)

#define queue_reverse_for_each(queue, node) \
    for (node = (queue)->tail; (node) != NULL; node = (node)->pre)

#define queue_is_empty(queue) \
    (((queue)->head == NULL) && ((queue)->tail == NULL))

#define queue_is_full(queue) \
    (((queue)->curr_size) >= ((queue)->init_size))

#define lock(queue) while (__sync_lock_test_and_set(&(queue)->lock,1)) {}

#define unlock(queue) __sync_lock_release(&(queue)->lock)

typedef struct node Node;
struct node {
    Node         *pre;
    Node         *next;
    void         *data;
};

typedef struct queue {
    Node         *head;
    Node         *tail;
    int           lock;
    unsigned int  init_size;
    unsigned int  curr_size; 
} Queue;

void queue_init (Queue *queue, unsigned int size);

void queue_insert_head (Queue *queue, Node *node);

void queue_insert_tail (Queue *queue, Node *node);

Node *queue_get_head (Queue *queue);

Node *queue_get_tail (Queue *queue);

void queue_destroy (void);

#endif /* !QUEUE_H */
