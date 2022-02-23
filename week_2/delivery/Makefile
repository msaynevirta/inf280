SRC_FILES=main.c
CFLAGS += -ansi -g -Wall -Wextra -Wno-missing-field-initializers

all: main

main: $(SRC_FILES)
	gcc $(CFLAGS) -o $@ $(SRC_FILES) -lm

clean:
	rm -f main

run: main
	# Running our main function from file main.c
	./main
