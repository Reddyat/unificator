all:
	make -C generator
	make -C unificator

test:
	make -C unificator test

clean:
	rm ./generator/generator
	rm ./unificator/unificator
