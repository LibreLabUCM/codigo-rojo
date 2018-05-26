OBJECTS = $(patsubst src/%.c, src/%.o, $(wildcard src/*.c))
HEADERS = $(wildcard src/*.h)
GCC = gcc -Wall

src/%.o: src/%.c $(HEADERS)
	$(GCC) -c $< -o $@

main: $(OBJECTS)
	$(GCC) $(OBJECTS) -o src/main

run: main
	./src/main

lib: $(OBJECTS)
	rm target/libcodp.a
	ar -cvq target/libcodp.a $(OBJECTS)

clean:
	rm src/*.o
	rm src/main
	rm target/libcodp.a
