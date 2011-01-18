.PHONY: all clean rebuild doc app

CD = cd
SRC_DIR = ./src
DOC_DIR = ./doc

all: clean rebuild

clean:
	${CD} ${DOC_DIR} ; ${MAKE} clean
	${CD} ${SRC_DIR} ; ${MAKE} clean

rebuild:
	${CD} ${SRC_DIR} ; ${MAKE} rebuild
	${CD} ${DOC_DIR} ; ${MAKE} rebuild	

doc:
	${CD} ${DOC_DIR} ; ${MAKE}

app:
	${CD} ${SRC_DIR} ; ${MAKE}
