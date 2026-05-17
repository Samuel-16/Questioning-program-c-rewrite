all: final/Simple\ questioning\ program

build:
	mkdir -p build

final:
	mkdir -p final

final/Simple\ questioning\ program: build/main.o build/program_functions.o final
	gcc build/main.o build/program_functions.o -o final/Simple\ questioning\ program -Os -flto -Wall -Werror
	echo '"Simple questioning program" created in the "final" directory.'

test: build/program_functions.o build/selfTest.o final
	gcc build/selfTest.o build/program_functions.o -o final/test -Os -flto -Wall -Werror
	./final/test
	echo "Testing complete!"

build/main.o: main.c build
	gcc main.c -c -o  build/main.o -Os -Wall -Werror

build/program_functions.o: program_functions.c build
	gcc program_functions.c -c -o  build/program_functions.o -Os -flto -Wall -Werror

build/selfTest.o: selfTest.c build
	gcc selfTest.c -c -o  build/selfTest.o -Os -flto -Wall -Werror

clean: build final
	rm -f build/* final/test
	rm -d build

full_clean: build final
	rm -f build/* final/*
	rm -d build final

.PHONY: all clean full_clean test