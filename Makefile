.PHONY: all clean rebuild doc app test

CD = cd
SRC_DIR = ./src
DOC_DIR = ./doc
TEST_DIR = ./tests

all: app doc test

clean:
	${CD} ${DOC_DIR} ; ${MAKE} clean
	${CD} ${SRC_DIR} ; ${MAKE} clean
	${CD} ${TEST_DIR} ; ${MAKE} clean

rebuild:
	${CD} ${SRC_DIR} ; ${MAKE} rebuild
	${CD} ${DOC_DIR} ; ${MAKE} rebuild	
	${CD} ${TEST_DIR} ; ${MAKE} rebuild	

doc:
	${CD} ${DOC_DIR} ; ${MAKE} all

app:
	${CD} ${SRC_DIR} ; ${MAKE} all

test: app
	${CD} ${TEST_DIR} ; ${MAKE} all
