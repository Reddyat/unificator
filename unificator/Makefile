CC=gcc
CFLAGS=-Wall -Wextra -O2
OBJ = main.o unificator_dynamic_array.o unificator_tools.o unificator_sort.o \
      unificator_timer.o unificator_socket.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

unificator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test: test_unificator_dynamic_array test_unificator_sort
	./test_unificator_dynamic_array
	./test_unificator_sort

test_unificator_dynamic_array: test_unificator_dynamic_array.o unificator_dynamic_array.o
	$(CC) -o $@ $^ $(CFLAGS)

test_unificator_sort: test_unificator_sort.o unificator_sort.o unificator_dynamic_array.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf unificator
	rm -rf test_unificator_dynamic_array