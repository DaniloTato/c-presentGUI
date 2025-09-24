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

If you prefer manual compilation, the equivalent g++ command is:

```bash
g++ -std=c++17 -Wall -Wextra \
    -Isrc -Iinclude -I./sfml/include -Ic-present/include \
    src/*.cpp c-present/src/*.c \
    -L./sfml/lib -lsfml-graphics -lsfml-window -lsfml-system -lcpresent \
    -o build/a -DPROJECT_ROOT="$(PWD)"
```

Adjust the -I and -L paths if SFML is installed elsewhere.