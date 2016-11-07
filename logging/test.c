/*
 * logger.c
 * Copyright (C) 2016 asxalex <asxalex@localhost>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <logging/logger.h>
#include <time.h>

int main() {
    const char *form = "[%(lineno): %(funcname)]: %(message)";
    formatter_t *formatter = new_formatter(form);
    handler_t *handler = new_handler(LEVEL_DEBUG, formatter);
    logger_t *logger = new_logger("logname", handler, "log.log");
    double start, end;
    start = clock();
    for (int i = 0; i < 1000000; i++) {
        makelog(logger, "this is a test for the make log", LEVEL_INFO);
    }
    end = clock();
    printf("%f seconds\n", (end-start)/CLOCKS_PER_SEC);
    destroy_logger(logger);
    return 0;
}
