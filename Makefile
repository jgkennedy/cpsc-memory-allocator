all: libmyalloc.so

libmyalloc.so:  allocator.c 
	clang -O2 -DNDEBUG -Wall -fPIC -shared -o libmyalloc.so allocator.c -ldl

clean:
	rm libmyalloc.so

