# c_present_gui

A small GUI demo using **SFML** and the **PRESENT cipher** (via `libcpresent`).

---

## Requirements

- C++17 or newer
- [SFML](https://www.sfml-dev.org/) installed (compiled or via package manager)
- [bear](https://github.com/rizsotto/Bear) (optional, only needed if you want `compile_commands.json` for clangd)
- `libcpresent` library (included as `c-present` submodule or folder)

By default, the Makefile expects SFML in `./sfml`.  
If you installed SFML with Homebrew, update `BREW_SFML` in the Makefile accordingly.

---

## Build with Make

```bash
make
```

This will:
	1.	Compile C++ source files from src/ and PRESENT library source from c-present/src/.
	2.	Place object files in build/.
	3.	Link the executable as build/a.

## Build without Make

If you prefer manual compilation, first compile the PRESENT library (`c-present`) as a static library:

```bash
gcc -std=c11 -Wall -Wextra -I./c-present/include -c c-present/src/*.c
ar rcs libc_present.a *.o
rm *.o
```

Then compile the GUI sources and link with SFML and the PRESENT library:

```bash
g++ -std=c++17 -Wall -Wextra \
    -I./sfml/include -I./c-present/include -I. \
    src/*.cpp \
    ./libc_present.a \
    -L./sfml/lib -lsfml-graphics -lsfml-window -lsfml-system \
    -o build/a \
    -DPROJECT_ROOT="\"$(PWD)\""
```

Make sure to adjust -I and -L paths if SFML is installed elsewhere, and ensure libc_present.a is in the current directory or library path.