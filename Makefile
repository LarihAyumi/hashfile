PROJ_NAME=ted

CC=gcc
CFLAGS=-std=c99 -Wall -g -fstack-protector-all

SRC=src/HashFile.c
OBJ=HashFile.o

all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) -o $(PROJ_NAME) $(OBJ)

HashFile.o: src/HashFile.c
	$(CC) -c $(CFLAGS) src/HashFile.c

test:
	$(CC) $(CFLAGS) tst/t_HashFile.c src/HashFile.c -o test
	./test

clean:
	rm -f *.o $(PROJ_NAME) test