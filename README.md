# c_present_gui

A small GUI demo using **SFML** and the **PRESENT cipher** (via `libcpresent`).

---

## Requirements

- C++17 or newer
- [SFML](https://www.sfml-dev.org/) installed (compiled or via package manager)
- [bear](https://github.com/rizsotto/Bear) (optional, only needed if you want `compile_commands.json` for clangd)
- `libcpresent` library (must be built and placed where the Makefile expects it)

By default, the Makefile looks for SFML in `./sfml`.  
If you installed SFML with Homebrew, you can symlink or update `BREW_SFML` in the Makefile.

---

## Build with Make

```bash
make

```

## Build without Make

If you prefer not to use the Makefile, you can compile manually with g++.
Here’s the equivalent command:

```bash
g++ -std=c++17 -Wall -Wextra \
    -Isrc -Iinclude -Isfml/include \
    src/*.cpp \
    -Lsfml/lib -lsfml-graphics -lsfml-window -lsfml-system -lcpresent \
    -o build/a -DPROJECT_ROOT=\"$(PWD)\"

```

•	Adjust the -Isfml/include and -Lsfml/lib paths if SFML is installed elsewhere (e.g., Homebrew default /opt/homebrew/opt/sfml).
•	Make sure libcpresent.a or libcpresent.dylib is in your library path.