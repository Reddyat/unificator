all:
	make -C generator
	make -C unificator

clean:
	rm ./generator/generator
	rm ./unificator/unificator
