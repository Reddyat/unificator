CC=gcc
CFLAGS=-Wall -Wextra -O2
OBJ = main.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

generator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o generator