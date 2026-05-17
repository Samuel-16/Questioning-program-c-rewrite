# About

This is an attempt to rewrite an old Python program from an A-level homework piece into C, by using the Python program as psudocode.

The program displays five randomly generated simple addition questions and takes answers from stdin. The results are saved to a file, along with a name. The program can display the scores from the file either by a specific name, or simply display all results for all names.

# Compiling

To compile the full program, you can run `make` in the program directory. This will create a directory called 'final', where the final program will be saved.

Run `make test` to compile and run the tests.

To delete the intermediate files created by the make process, run `make clean`. To also delete the 'final' directory, you can run `make full_clean`.

# Quirks of C learned

- A 'char' is simply a one byte integer. Utf-8 used multiple bytes for non ASCII characters, so characters like `'ア'` would actually take up multiple 'characters'.
- Structs cannot be given default values. A constant needs to be used to initialise them.
- Unlike arrays, structs can be passed by value.
- Arrays can only assigned to array variables when the array is declared. Other functions need to be used to modify an already declared array unless you go one element at a time.
- ~~You cannot do `char nameString[255]=""`. Initialising an array with a value only allocates the space needed for that value.~~ This is incorrect. Arrays can actually be allocated a larger space than their initial value. I misunderstood an error. You can initialise an array this way with a magic number, but not a const.
- Mixing `scanf` and `fgets` causes issues, as `scanf` leaves the newline character in stdin and causes `fgets` to immediately receive an empty string.
- C files can be compiled into object files if they are missing definitions for functions or global variables that are nonetheless declared. These files can then be combined with other object files which *do* possess the necessary definitions to build the final executable.
- "Make" and "Cmake" are different. Make is for automating the process of compiling multiple pieces of source code at the same time into intermediate files, which can then be merged into a single, final, executable.
- Header files are files containing C code that do not make a full C file by themselves. They simply contain struct or keyword definitions, or declarations of undefined data, which can then be included by multiple C files, rather than be individually written in each.

# Issues

- An issue from the original program is that it writes to the output file as it takes an answer to each individual question, meaning that the file becomes invalid if the program is terminated while midway through questioning. This issue has been fixed in the C code.