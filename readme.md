# Iowa

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen.svg)](#)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](#)

Iowa is a simple, high‑level interpreted language designed for readability. Inspired by modern scripting languages, Iowa offers a clean syntax, dynami typing

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
bin/Iowa path/to/script.ia
```

---

Run it:

```bash
bin/iowa hello.ia
# Output: Hello, World!
```

## Examples
```Iowa++
set hello = (false || true);

set z = false;

say (hello);
say (z && hello);


set x = (5 + (3 + 2));
set y = 3;

{
    set x = 3;
    set y = 3;
    say (x * y);
}

say (x * y);
```
# Output: 
```bash
true
false
9
30
```
