all:
	make -C generator
	make -C unificator

test:
	make -C unificator test

clean:
	make -C generator clean
	make -C unificator clean
