# Iowa

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](#)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](#)

Iowa is a simple, high‑level interpreted language designed for readability. Inspired by modern scripting languages, Iowa offers a clean syntax, dynamic typing

---

## Table of Contents

1. [Features](#features)
2. [Prerequisites](#prerequisites)
4. [Building from Source](#building-from-source)
5. [Running Tests](#running-tests)
6. [Usage](#usage)
7. [Examples](#examples)

---

## Features

* **Interpreted**: No compilation step—run scripts directly.
* **High-Level Syntax**: Clean, human-readable code.
* **Dynamic Typing**
* **Platform**: Anything Unix

---

## Prerequisites

Before you begin, ensure you have the following installed on your system:

* `clang`
* GNU Make
* [Git](https://git-scm.com/)

---

## Building from Source

Use `make` to compile the interpreter:

```bash
make
```

The executable will be placed in the bin folder.


---

## Running Tests

Build and run tests

```bash
make run 
# or
./run.sh
```

---

## Usage

Invoke the interpreter with a script path:

```bash
./bin/Iowa path/to/script.ia
```

---

Run it:

```bash
./bin/iowa hello.ia
```
# Examples

## Example 1
```iowa++
set number = 3;

console_out (number == 5);

if (number == 5) {
    console_out ("number is 5");
}
else {
    console_out ("number is not 5");
}

```
### Output: 
```bash
false
number is not 5
```

## Example 2
```iowa++
console_out ((((2 + (5 * (3 - 1))) + 1) + (4 - 3) + 3) + (3 + 3) + (4 / 2) / (9 * 2));
console_out (false && (false || true) || (false && false));
```

### Output:
```bash
23
false
```

## Example 3
```iowa++
set x = 5;
set y = 2;

console_out(x*y);

{
    set x = 2;
    console_out(x*y);
    
    if (x*y == 4){
        console_out("Hello World!");
    }
    else {
        console_out("Goodbye World!");
    }
}
```

### Output:
```bash
10
4
Hello World!
```







