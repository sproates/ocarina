# Copyright 2011 Ian Sproates <ian@sproates.net>

.PHONY: all clean rebuild

CC = gcc
RM = rm -rf
SRC_DIR = ../src
DOXYGEN = doxygen
DOXYGEN_DIR = ./doxygen

all: ${DOXYGEN_DIR}

rebuild: clean all

clean:
	${RM} ${DOXYGEN_DIR}

${DOXYGEN_DIR}:
	${DOXYGEN} doxygen.config
