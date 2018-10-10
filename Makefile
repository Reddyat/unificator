all:
	make -C generator
	make -C unificator
	./unificator/unificator