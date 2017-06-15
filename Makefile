.PHONY: all

all: lib
	@ gcc -I./ -o pyrin *.c

obj:
	@ gcc -fPIC -c -I./ strops.c pyrin.c

lib: obj
	@ gcc -shared -o libpyrin.so pyrin.o strops.o

test-lib: lib
	@ gcc -L$(PWD) -I./ -o test-lib main.c $(PWD)/libpyrin.so

run:
	@ ./pyrin

clean:
	@ rm pyrin test-lib *.o *.so 2> /dev/null

test: all
	@ ./pyrin | grep "$(node js/test_all.js)" | wc -l
