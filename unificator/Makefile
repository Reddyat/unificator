CC=gcc
CFLAGS=-Wall -Wextra -O2
OBJ = main.o unificator_dynamic_array.o unificator_tools.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

unificator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o unificator