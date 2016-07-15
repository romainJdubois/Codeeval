INCL_DIR=../include
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)
EXEC=alignement

CFLAGS=-W -Wall -I${INCL_DIR}
LDFLAGS=

all: ${EXEC}

${EXEC}: ${OBJ}
	$(CC) -o $@ $^ ${LDFLAGS}

%.o: %.c
	$(CC) -o $@ -c $< ${CFLAGS}

.PHONY: clean mrproper

clean:
	@rm -rf *.o

cleaner: clean
	@rm -rf $(EXEC)
