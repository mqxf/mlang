sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g -Wall -lm -ldl -fPIC -rdynamic\

mlang: $(objects)
	gcc $(objects) $(flags) -o mlang

%.o: %.c include/%.h
	gcc -c $(flags) $< -o $@

install:
	sudo mkdir -p /usr/local/include/mlang
	sudo cp -r ./src/include/* /usr/local/include/mlang/.
	make
	sudo cp ./mlang /usr/local/bin/mlang
	make clean

clean:
	-rm mlang
	-rm *.o
	-rm *.a
	-rm src/*.o

lint:
	clang-tidy src/*.c src/include/*.h
