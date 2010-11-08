.PHONY: all clean test

ECHO = /usr/bin/echo
RM = /usr/bin/rm

all: ocarina

ocarina:
	@${ECHO} building

clean:
	@${ECHO} cleaning up
test:
	@${ECHO} testing