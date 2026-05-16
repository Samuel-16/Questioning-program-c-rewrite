all: program

build:
	mkdir -p build

final:
	mkdir -p final

program: build/main.o build/program_functions.o final
	gcc build/main.o build/program_functions.o -o final/Simple\ questioning\ program -Os -Wall -Werror
	echo '"Simple questioning program" created in the "final" directory.'

test: build/program_functions.o build/selfTest.o final
	gcc build/selfTest.o build/program_functions.o -o final/test -Os -Wall -Werror
	./final/test

build/main.o: main.c build
	gcc main.c -c -o  build/main.o -Os -Wall -Werror

build/program_functions.o: program_functions.c build
	gcc program_functions.c -c -o  build/program_functions.o -Os -Wall -Werror

build/selfTest.o: selfTest.c build
	gcc selfTest.c -c -o  build/selfTest.o -Os -Wall -Werror

clean:
	rm -f build/* final/test

full_clean:
	rm -f build/* final/*

.PHONY: all program clean full_clean test