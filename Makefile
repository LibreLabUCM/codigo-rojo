OBJECTS = $(patsubst src/%.c, src/%.o, $(wildcard src/*.c))
HEADERS = $(wildcard src/*.h)
GCC = gcc -Wall

src/%.o: src/%.c $(HEADERS)
	$(GCC) -c $< -o $@

main: $(OBJECTS)
	$(GCC) $(OBJECTS) -o src/main

run: main
	./src/main

clean:
	rm src/*.o
	rm src/main
