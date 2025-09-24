# ------------------------
# Project settings
# ------------------------
target := a

source_dir  := src
include_dir := include
build_dir   := build

external_dir := c-present
external_src := $(shell find $(external_dir)/src -name '*.c' -o -name '*.cpp')
external_inc := $(external_dir)/include

# ------------------------
# Sources and objects
# ------------------------
sources := $(shell find $(source_dir) -name '*.cpp') $(external_src)
headers := $(shell find $(include_dir) -name '*.hpp') \
           $(shell find $(external_inc) -name '*.h' -o -name '*.hpp')

objs := $(patsubst %.cpp,$(build_dir)/%.o,$(filter %.cpp,$(sources))) \
        $(patsubst %.c,$(build_dir)/%.o,$(filter %.c,$(sources)))

# ------------------------
# Compiler and flags
# ------------------------
CXX    := g++
CC     := gcc
CXXSTD := c++17

BREW_SFML := ./sfml

CXXFLAGS := -Wall -Wextra -std=$(CXXSTD) \
            -I$(include_dir) \
            -I$(BREW_SFML)/include \
            -I$(external_inc) \
            -I$(PWD) \
            -DPROJECT_ROOT=\"$(PWD)\"

CFLAGS := -Wall -Wextra -std=c11 \
          -I$(external_inc)

LIB_SFML := -L$(BREW_SFML)/lib -lsfml-graphics -lsfml-window -lsfml-system

ifeq ($(BUILD),release)
	target += _release
	CXXFLAGS += -O2
else
	CXXFLAGS += -g
endif

CLANGDB := compile_commands.json
MAKEFLAGS += --no-print-directory

# ------------------------
# Targets
# ------------------------
all: $(target)

$(target): $(build_dir)/$(target)

.PHONY: all format lint lint-fix clangdb clean clean-clangdb clean-all

# ------------------------
# Utility rules
# ------------------------
format:
	@clang-format -i $(headers) $(sources)

lint: $(CLANGDB)
	@clang-tidy $(headers) $(sources) -p .

lint-fix: $(CLANGDB)
	@clang-tidy $(headers) $(sources) -p . --fix

clangdb: clean-clangdb
	@$(MAKE) $(CLANGDB)

# ------------------------
# Build rules
# ------------------------
$(build_dir)/$(target): $(objs) | $(build_dir)
	@echo "Linking $@"
	@$(CXX) $^ $(CXXFLAGS) $(LIB_SFML) -o $@

# Compile C++ sources
$(build_dir)/%.o: %.cpp | $(build_dir)
	@mkdir -p $(dir $@)
	@echo "Compiling C++ $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C sources
$(build_dir)/%.o: %.c | $(build_dir)
	@mkdir -p $(dir $@)
	@echo "Compiling C $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# Generate compile_commands.json with bear
$(CLANGDB):
	@$(MAKE) clean
	@bear -- $(MAKE) $(objs)

# Ensure build directory exists
$(build_dir):
	@mkdir -p $(build_dir)

# ------------------------
# Clean rules
# ------------------------
clean:
	@find $(build_dir) -name '*.o' -exec rm -f {} +
	@rm -rf $(build_dir)

clean-clangdb:
	@rm -f $(CLANGDB)
	@rm -rf .cache/clangd

clean-all: clean clean-clangdb