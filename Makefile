OBJECTS = $(patsubst src/%.c, src/%.o, $(wildcard src/*.c))
HEADERS = $(wildcard src/*.h)

src/%.o: src/%.c $(HEADERS)
	gcc -c $< -o $@

main: $(OBJECTS)
	gcc $(OBJECTS) -Wall -o src/main

run: main
	./src/main

clean:
	rm src/*.o
	rm src/main
