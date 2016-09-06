#include <stdio.h>
#include "queue.h"

void *
call_func (void *data)
{
    Node      *node;
    Queue     *queue; 

    queue = (Queue *) data;

    if ((node = queue_get_tail (queue)) != NULL) {
        printf("%d\n", *(int*)node->data);
    }
    else {
        printf ("queue is empty\n");
    }

    return NULL;
}

int
main (void)
{
    int        i;
    int        data[10000];
    Node       node[10000];
    pthread_t  tid[10000];

    Queue queue;
    queue_init (&queue);

    for (i = 0; i < 10000; i++) {
        data[i] = i;
        node[i].data = &data[i];

        queue_insert_head (&queue, &node[i]);
    }

    /*
    Node *tmp;

    queue_for_each (&queue, tmp) {
        printf("%d\n", *(int*)tmp->data);
    }

    queue_reverse_for_each (&queue, tmp) {
        printf("%d\n", *(int*)tmp->data);
    }

    printf ("start delete test...\n");
    while ((tmp = queue_get_tail (&queue)) != NULL) {
        printf("%d\n", *(int*)tmp->data);
    }

    if (is_empty (&queue)) {
        printf("queue is emptry\n"); 
    }
    */

    for (i = 0; i < 10000; i++) {
        pthread_create (&tid[i], NULL, call_func, &queue);
    }

    for (i = 0; i < 10000; i++) {
        pthread_join (tid[i], NULL);
    }

    /*
    printf ("start delete test...\n");
    while ((tmp = queue_get_head (&queue)) != NULL) {
        printf("%d\n", *(int*)tmp->data);
    }
    */
}
