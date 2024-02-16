# Enable debugging and suppress pesky warnings
CFLAGS ?= -g -w 

all:	vulfoo

clean:
	rm -f vulfoo

vulfoo: vulfoo.c
	${CC} ${CFLAGS} vulfoo.c -o vulfoo
