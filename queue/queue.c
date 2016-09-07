#include "queue.h"
#include <stdlib.h>

static pthread_mutex_t mutex;

void
queue_init (Queue *queue, unsigned int size) {
    pthread_mutex_init (&mutex, NULL);
    queue->head = queue->tail = NULL;
    queue->init_size = size; 
    queue->curr_size = 0;
}

void
queue_insert_head (Queue *queue, Node *node) { 
    
    while (queue_is_full (queue));

    lock (queue);

    if (queue_is_empty (queue)) {
        queue->tail = queue->head = node;
        node->pre = node->next = NULL;
    } else {
        node->pre  = NULL;
        node->next = queue->head;
        node->next->pre = node;
        queue->head = node;
    }

    queue->curr_size++;

    unlock (queue);
}

void
queue_insert_tail (Queue *queue, Node *node) {

    while (queue_is_full (queue));

    lock (queue);

    if (queue_is_empty (queue)) {
        queue->tail = queue->head = node;
        node->pre = node->next = NULL;
    } else {
        node->next = NULL;
        node->pre = queue->tail;
        queue->tail->next = node;
        queue->tail = node;
    }

    queue->curr_size++;

    unlock (queue);
}

/*it willl delete the queue's head element and return it'*/
Node *
queue_get_head (Queue *queue) {
    Node    *tmp;
    Node    *next;

    pthread_mutex_lock (&mutex);

    while (queue_is_empty (queue));

    pthread_mutex_unlock (&mutex);

    if ( (tmp = queue->head) != NULL) {
        if ( (next = tmp->next) != NULL) {
            next->pre = NULL;
            queue->head = next;
        } else {
            queue->head = queue->tail = NULL;
        }
    } else {
        unlock (queue);
        while (queue_is_empty (queue));
        lock (queue);
    }

    queue->curr_size--;

    unlock (queue);

    return tmp;
}

/*it willl delete the queue's tail element and return it'*/
Node *
queue_get_tail (Queue *queue) {
    Node    *tmp; 
    Node    *pre;

    pthread_mutex_lock (&mutex);

    while (queue_is_empty (queue));

    pthread_mutex_unlock (&mutex);

    lock (queue);

    if ( (tmp = queue->tail) != NULL) {
        if ( (pre = tmp->pre) != NULL) {
            pre->next = NULL;
            queue->tail = pre;
        } else {
            queue->head = queue->tail = NULL;
        }
    }

    queue->curr_size--;

    unlock (queue);

    return tmp;
}

void
queue_destroy (void) {
    pthread_mutex_destroy(&mutex);
}
