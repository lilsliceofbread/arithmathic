# arithmathic

c library of various maths functions

indefinitely on hiatus (evaluate_expression does not work with brackets)

# compiling

requires GCC

run `make -C src` to build the static library

if you have linking errors on Windows try changing NAME in *src/Makefile* to the .lib extension instead of .a

to build the examples run `make -C examples`

# using the library

linking dependencies: libc math (`-lm`)

see *example/Makefile* LD_FLAGS for details