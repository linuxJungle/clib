#include "queue.h"

static pthread_mutex_t mutex;

void
queue_init (Queue *queue) {
    pthread_mutex_init (&mutex, NULL);
    queue->head = queue->tail = NULL;
}

void
queue_insert_head (Queue *queue, Node *node) { 

    pthread_mutex_lock (&mutex);

    if (queue_is_empty (queue)) {
        queue->tail = queue->head = node;
        node->pre = node->next = NULL;
    } else {
        node->pre  = NULL;
        node->next = queue->head;
        node->next->pre = node;
        queue->head = node;
    }

    pthread_mutex_unlock (&mutex);
}

void
queue_insert_tail (Queue *queue, Node *node) {

    pthread_mutex_lock (&mutex);

    if (queue_is_empty (queue)) {
        queue->tail = queue->head = node;
        node->pre = node->next = NULL;
    } else {
        node->next = NULL;
        node->pre = queue->tail;
        queue->tail->next = node;
        queue->tail = node;
    }

    pthread_mutex_unlock (&mutex);
}

/*it willl delete the queue's head element and return it'*/
Node *
queue_get_head (Queue *queue) {
    Node    *tmp;
    Node    *next;

    pthread_mutex_lock (&mutex);

    tmp = queue->head;

    if (tmp != NULL) {
        next = tmp->next;
        if ( (next = tmp->next) != NULL) {
            next->pre = NULL;
            queue->head = next;
        } else {
            queue->head = queue->tail = NULL;
        }
    }

    pthread_mutex_unlock (&mutex);

    return tmp;
}

/*it willl delete the queue's tail element and return it'*/
Node *
queue_get_tail (Queue *queue) {
    Node    *tmp; 
    Node    *pre;

    pthread_mutex_lock (&mutex);

    tmp = queue->tail;

    if (tmp != NULL) {
        if ( (pre = tmp->pre) != NULL) {
            pre->next = NULL;
            queue->tail = pre;
        } else {
            queue->head = queue->tail = NULL;
        }
    } 

    pthread_mutex_unlock (&mutex);

    return tmp;
}

void
queue_destroy (void) {
    pthread_mutex_destroy(&mutex);
}

