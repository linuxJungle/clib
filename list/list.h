/*
 * list.h
 * Copyright (C) 2016 alex <alex@alex>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef LIST_H
#define LIST_H

typedef struct list_node_s {
    struct list_node_s *next;
} list_node_t;

typedef struct list_s {
    struct list_node_s *head;
    struct list_node_s *tail;
} list_t;

void __reverse_list__(list_t *list);
void __list_insert_tail__(list_t *list, list_node_t *node);
void __list_insert_head__(list_t *list, list_node_t *node);

/* the list is a pointer, and the node is a pointer too. */
#define init_list_head(list) \
    (list)->head = (list)->tail = NULL

#define is_empty(list) \
    (((list)->head == NULL) && ((list)->tail == NULL))

#define reverse_list(list) \
    __reverse_list__(list)

#define is_singular(list) \
    (((list)->head) == ((list)->tail) && (list)->head != NULL)

#define list_insert_head(list, node) \
    __list_insert_head__(list, node)

#define list_insert_tail(list, node) \
    __list_insert_tail__(list, node)

#define element_of(ptr, type, member) \
    (type*)((unsigned char*)(ptr) - (unsigned char *)(&(((type*)0)->member)))

#define list_for_each(list, iter) \
    for ((iter) = (list)->head; (iter); (iter) = (iter)->next)

#define list_safe_for_each(list, iter, next) \
    for ((iter) = (list)->head, (next) = ((iter) ? (iter)->next : NULL); \
         (iter); \
         (iter) = (next != NULL ? next : NULL), (next) = ((next) != NULL ? (next)->next : NULL))

#endif /* !LIST_H */
