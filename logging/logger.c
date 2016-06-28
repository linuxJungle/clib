/*
 * logger.c
 * Copyright (C) 2016 asxalex <asxalex@localhost>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "logger.h"
#include "list.h"
#include <time.h>

const char *FORMATTER_IDENTIFIERS[NUMBER_OF_FORMATTER_OPTIONS] = {
    "name",
    "levelno",
    "levelname",
    "pathname",
    "filename",
    "module",
    "funcname",
    "lineno",
    "created",
    "asctime",
    "msecs",
    "threadname",
    "process",
    "message",
};

static void __die__(const char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(-1);
}

static int __read_until__(int from, const char target, const char *content) {
    int length = strlen(content);
    if (from >= length) {
        return -1;
    }
    char ch = content[from];
    while ((from < length) && (ch != target)) {
        from += 1;
        ch = content[from];
    }

    if (from == length) {
        return -1;
    }
    return from;
}

static formatter_node_t* __create_node__(int from, int to, const char *s) {
    formatter_node_t *node = malloc(sizeof(struct formatter_node_s));
    if (node == NULL) {
        __die__("no space for node");
    }
    if ((s[from] == '%') && (s[from+1] == '(') && (s[to] == ')')) {
        node->type = LOG_FORMAT_OPTION;
        from = from + 2;
        to = to - 1;
        if (from == to) {
            __die__("no such format %()");
        }

        int i = 0;
        for (i = 0; i < NUMBER_OF_FORMATTER_OPTIONS; i++){
            if (strncmp(s+from, FORMATTER_IDENTIFIERS[i], (to-from+1)) == 0) {
                node->content.option = i;
                break;
            }
        }
        if (i == NUMBER_OF_FORMATTER_OPTIONS) {
            __die__("no such format");
        }
    } else {
        node->type = LOG_FORMAT_LITERAL;
        char *temp = malloc(sizeof(char) * (to-from+2));
        if (temp == NULL) {
            __die__("no more space for temp string");
        }
        strncpy(temp, s+from, to-from+1);
        temp[to-from+1] = '\0';
        node->content.literal = temp;
    }
    return node;
}

formatter_t* new_formatter(const char *form) {
    int from = 0;
    int to;
    int length = strlen(form);
    formatter_t *formatter = malloc(sizeof(formatter_t));
    if (formatter == NULL) {
        __die__("failed to alloc formatter");
    }
    init_list_head(formatter);
    int count = 0;
    while ((from < length) && (from != -1)) {
        to = __read_until__(from, '%', form);
        if (to == -1) {
            to = length - 1;
        } else if (to == from) {
            to = __read_until__(from, ')', form);
        } else {
            to -= 1;
        }
        formatter_node_t *temp = __create_node__(from, to, form);
        if (temp == NULL) {
            continue;
        }

        list_insert_tail(formatter, &(temp->node));

        from = to + 1;
    }
    return formatter;
}

handler_t* new_handler(LOG_LEVEL level, formatter_t *formatter) {
    if (formatter == NULL) {
        const char *form = "%(name)abc";
        formatter_t *formatter = new_formatter(form);
    }
    handler_t *handler = malloc(sizeof(handler_t));
    if (!handler) {
        __die__("no enough space for handler");
    }
    handler->level = level;
    handler->formatter = formatter;
    return handler;
}

logger_t* new_logger(const char *logname, handler_t *handler, const char *filename) {
    logger_t *logger = malloc(sizeof(logger_t));
    if (!logger) {
        __die__("no enough space for logger");
    }
    if (!handler) {
        handler = new_handler(LEVEL_DEBUG, NULL);
    }
    logger->name = logname;
    logger->fp = fopen(filename, "a+");
    logger->handler = handler;
    logger->size = logger->index = 0;
    return logger;
}

void destroy_formatter(formatter_t *formatter) {
    formatter_node_t *formatter_node;
    list_node_t *node;
    list_node_t *next;
    list_safe_for_each(formatter, node, next) {
        formatter_node = element_of(node, formatter_node_t, node);
        if (formatter_node->type == LOG_FORMAT_LITERAL) {
            free(formatter_node->content.literal);
            free(formatter_node);
        }
    }
    free(formatter);
    formatter = NULL;
}

void destroy_handler(handler_t *handler) {
    if (handler->formatter) {
        destroy_formatter(handler->formatter);
        handler->formatter = NULL;
    }
    free(handler);
    handler = NULL;
}

void destroy_logger(logger_t *logger) {
    if (logger->handler) {
        destroy_handler(logger->handler);
        logger->handler = NULL;
    }
    fclose(logger->fp);
    free(logger);
    logger = NULL;
}

void makelog_inner(int line, const char *funcname, logger_t *logger, const char *msg, LOG_LEVEL level) {
    if (logger->handler->level > level) {
        return;
    }

    FILE *fp = logger->fp;
    formatter_t *formatter = logger->handler->formatter;
    formatter_node_t *formatter_node;
    list_node_t *node;
    list_for_each(formatter, node) {
        formatter_node = element_of(node, formatter_node_t, node);
        switch (formatter_node->type) {
        case LOG_FORMAT_OPTION: 
            switch (formatter_node->content.option) {
                case FORMATTER_NAME:
                    fprintf(fp, "%s", logger->name);
                    break;
                case FORMATTER_LEVELNO:
                    fprintf(fp, "%d", logger->handler->level);
                    break;
                case FORMATTER_LEVELNAME:
                    fprintf(fp, "%s", "levelname");
                    break;
                case FORMATTER_FUNCNAME:
                    fprintf(fp, "%s", funcname);
                    break;
                case FORMATTER_LINENO:
                    fprintf(fp, "%d", line);
                    break;
                case FORMATTER_MESSAGE:
                    fprintf(fp, "%s", msg);
                    break;
                default:
                    break;
            }
            break;
        case LOG_FORMAT_LITERAL:
            fprintf(fp, "%s", formatter_node->content.literal);
            break;
        }
    }
    fprintf(fp, "\n");
}
