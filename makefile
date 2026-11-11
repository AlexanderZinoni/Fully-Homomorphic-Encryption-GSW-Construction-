all= main

CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -lm
LDLIBS = -lm

INC = include
SRC = src

main: main.o vector.o GSW.o
	$(CC) $(CFLAGS) main.o vector.o GSW.o -o main $(LDLIBS)

vector.o: $(SRC)/vector.c $(INC)/vector.h
	$(CC) $(CFLAGS) -c $< -o $@

GSW.o: $(SRC)/GSW.c $(INC)/GSW.h $(INC)/vector.h
	$(CC) $(CFLAGS) -c $< -o $@

main.o: $(SRC)/main.c $(INC)/vector.h $(INC)/GSW.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o main