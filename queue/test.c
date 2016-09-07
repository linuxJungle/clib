#include <stdio.h>
#include "queue.h"

struct call_data {
    Queue *queue;
    Node  *node;
};

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

void *
call_func2 (void *data) {

    struct call_data * tmp = (struct call_data *) data;
    queue_insert_head (tmp->queue, tmp->node); 

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
    queue_init (&queue, 130);
    set_block(&queue);


    for (i = 0; i < 130; i++) {
        pthread_create (&tid[i], NULL, call_func, &queue);
    }

    for (i = 0; i < 130; i++) {
        data[i] = i;
        node[i].data = &data[i];

        queue_insert_head (&queue, &node[i]);
    }

    //printf("curr_size %d\t init_size %d\n", queue.curr_size, queue.init_size);

    for (i = 0; i < 130; i++) {
        pthread_join (tid[i], NULL);
    }


    //printf("curr_size %d\t init_size %d\n", queue.curr_size, queue.init_size);

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

    /*
    printf ("start delete test...\n");
    while ((tmp = queue_get_head (&queue)) != NULL) {
        printf("%d\n", *(int*)tmp->data);
    }
    */
    queue_destroy();
}
