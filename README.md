# BISONTE 2.0

This repository contains a toy interpreter built with **flex** and **bison**.

## Build prerequisites
- `bison`
- `flex`
- `g++` and `make`

On Debian/Ubuntu systems you can install them via:
```sh
sudo apt-get install bison flex g++ make
```

## Building
Run `make` from the repository root. This will compile the interpreter and all
subcomponents, producing `interpreter.exe`.

## Running

You can execute a program by passing the file path:
```sh
./interpreter.exe program.p

Several sample programs live in the `examples/` directory. They are
interactive, so they will prompt for input when run. To convert a number to
binary you can execute:
```sh
./interpreter.exe examples/binario.p
```
Other examples (`conversion.p`, `menu.p`, `test_switch.p`) exercise different
language features such as type conversion, menus and switch statements. The
`strings.p` example demonstrates string variables.  The new
`full_example.p` program combines nearly all supported constructs:
```sh
./interpreter.exe examples/strings.p
./interpreter.exe examples/full_example.p
```
