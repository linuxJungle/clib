#! /usr/bin/env python
# -*- coding: utf-8 -*-
# vim:fenc=utf-8
#
# Copyright © 2016 alex <alex@alex>
#
# Distributed under terms of the MIT license.
import logging
import time

def main():
    logger=logging.getLogger()
    handler=logging.FileHandler("Log_test.txt")
    formatter = logging.Formatter('[%(lineno)d:%(funcName)s]: %(message)s')
    handler.setFormatter(formatter)
    logger.addHandler(handler)
    logger.setLevel(logging.DEBUG)

    start = time.time()
    for i in range(1000000):
        logger.debug("this is a test for the make log")
    end = time.time()
    print "%d seconds" % (end - start)

if __name__ == "__main__":
    main()
