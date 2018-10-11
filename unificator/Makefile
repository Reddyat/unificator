CC=gcc
CFLAGS=-Wall -Wextra -g
OBJ = main.o unificator_dynamic_array.o unificator_tools.o
TEST_OBJ = unificator_dynamic_array.o

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

unificator: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

test: test_unificator_dynamic_array
	./test_unificator_dynamic_array

test_unificator_dynamic_array: test_unificator_dynamic_array.o unificator_dynamic_array.o
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -rf *.o
	rm -rf unificator
	rm -rf test_unificator_dynamic_array