CC=gcc
CFLAGS=-I. -Wall -Werror
OBJ = main.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

unificator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o unificator