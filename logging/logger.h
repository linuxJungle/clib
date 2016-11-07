/*
 * logger.h
 * Copyright (C) 2016 asxalex <asxalex@localhost>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef LOGGER_H
#define LOGGER_H

#define FORMATTER_TO_STR(format) "FORMATTER_"#format
#include <list/list.h>
#define BUF_SIZE 1024

typedef enum {
    LEVEL_DEBUG,
    LEVEL_INFO,
    LEVEL_WARNING,
    LEVEL_ERROR,
    LEVEL_CRITICAL,
} LOG_LEVEL;

typedef enum {
    FORMATTER_NAME,
    FORMATTER_LEVELNO,
    FORMATTER_LEVELNAME,
    FORMATTER_PATHNAME,
    FORMATTER_FILENAME,
    FORMATTER_MODULE,
    FORMATTER_FUNCNAME,
    FORMATTER_LINENO,
    FORMATTER_CREATED,
    FORMATTER_ASCTIME,
    FORMATTER_MSECS,
    FORMATTER_THREADNAME,
    FORMATTER_PROCESS,
    FORMATTER_MESSAGE,

    NUMBER_OF_FORMATTER_OPTIONS,
} LOG_FORMATTER_OPTIONS;


typedef enum {
    LOG_FORMAT_OPTION,
    LOG_FORMAT_LITERAL,
} LOG_FORMATTER_TYPE;

typedef struct formatter_node_s {
    union {
        LOG_FORMATTER_OPTIONS option;
        char *literal;
    } content;
    LOG_FORMATTER_TYPE type;
    list_node_t node;
}formatter_node_t;

typedef list_t formatter_t;

typedef struct handler_s {
    LOG_LEVEL level;
    formatter_t *formatter;
} handler_t;

typedef struct logger_s {
    const char *name;
    handler_t *handler;
    FILE *fp;
    char buffer[BUF_SIZE];
    int size;
    int index;
} logger_t;

formatter_t* new_formatter(const char *form);
handler_t* new_handler(LOG_LEVEL level, formatter_t *formatter);
logger_t* new_logger(const char *logname, handler_t *handler, const char *);
void destroy_logger(logger_t *logger);
void destroy_handler(handler_t *handler);
void destroy_formatter(formatter_t *formatter);
void makelog_inner(int line, const char *funcname, logger_t *logger, const char *msg, LOG_LEVEL level);

#define makelog(l, msg, level) \
    makelog_inner(__LINE__, __func__, l, msg, level)

#endif /* !LOGGER_H */
