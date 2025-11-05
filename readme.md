# About

This is an attempt to rewrite an old Python program from an A-level homework piece into C, by using the Python program as psudocode.

The program displays five randomly generated simple addition questions and takes answers from stdin. The results are saved to a file, along with a name. The program can display the scores from the file either by a specific name, or simply display all results for all names.

# Compiling

A line of shell script has been included named `export.sh` to compile the C program and save it to the parent directory.

# Querks of C learned

- A 'char' is simply a one byte integer. Utf-8 used multiple bytes for non ascii characters, so characters like `'ア'` would actually take up multiple characters.
- Structs cannot be given default values. A constant to be used to initalise them.
- Unlike arrays, structs can be passed by value.
