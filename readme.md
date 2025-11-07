# About

This is an attempt to rewrite an old Python program from an A-level homework piece into C, by using the Python program as psudocode.

The program displays five randomly generated simple addition questions and takes answers from stdin. The results are saved to a file, along with a name. The program can display the scores from the file either by a specific name, or simply display all results for all names.

# Compiling

A line of shell script has been included named `export.sh` to compile the C program and save it to the parent directory.

# Quirks of C learned

- A 'char' is simply a one byte integer. Utf-8 used multiple bytes for non ASCII characters, so characters like `'ア'` would actually take up multiple 'characters'.
- Structs cannot be given default values. A constant needs to be used to initialise them.
- Unlike arrays, structs can be passed by value.
- Arrays can only assigned to array variables when the array is declared. Other functions need to be used to modify an already declared array unless you go one element at a time.
- You cannot do `char nameString[255]=""`. Initialising an array with a value only allocates the space needed for that value.
- Mixing `scanf` and `fgets` causes issues, as `scanf` leaves the newline character in stdin and causes `fgets` to immediately receive an empty string.

# Issues

- An issue from the original program is that it writes to the output file as it takes an answer to each individual question, meaning that the file becomes invalid if the program is terminated while midway through questioning. For the time being, this issue has been ported.
