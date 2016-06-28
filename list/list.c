/*
 * list.c
 * Copyright (C) 2016 alex <alex@alex>
 *
 * Distributed under terms of the MIT license.
 */

#include "list.h"
#include <stdio.h>

void __reverse_list__(list_t *list) {
    struct list_node_s *temp = list->head;
    list->head = list->tail;
    list->tail = temp;
}

void __list_insert_tail__(list_t *list, list_node_t *node) {
    if (is_empty(list)) {
        list->head = node;
        list->tail = node;
        node->next = NULL;
    } else {
        node->next = NULL;
        list->tail->next = node;
        list->tail = node;
    }
}

void __list_insert_head__(list_t *list, list_node_t *node) {
    if (is_empty(list)) {
        list->head = node;
        list->tail = node;
        node->next = NULL;
    } else {
        node->next = list->head;
        list->head = node;
    }
}
