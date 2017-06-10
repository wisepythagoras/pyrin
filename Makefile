.PHONY: all

all: lib
	@ gcc -I./ -o pyrin_test *.c

obj:
	@ gcc -fPIC -c -I./ -o libpyrin.o pyrin.c

lib: obj
	@ gcc -shared -o libpyrin.so libpyrin.o

test-lib:
	#@ export LD_LIBRARY_PATH=$(PWD):$LD_LIBRARY_PATH
	@ gcc -L$(PWD) -I./ -o test_lib main.c $(PWD)/libpyrin.so

run:
	@ ./pyrin_test

clean:
	@ rm pyrin_test test_lib 2> /dev/null
	@ rm *.o *.so 2> /dev/null
