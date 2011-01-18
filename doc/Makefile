# Copyright 2011 Ian Sproates <ian@sproates.net>

.PHONY: all clean rebuild

CC = gcc
RM = rm -rf
SRC_DIR = ../src

DOXYGEN = doxygen
DOXYGEN_DIR = ./doxygen

rebuild: clean all

clean:
	${RM} ${DOXYGEN_DIR}

all: doxygen.config
	${DOXYGEN} doxygen.config
