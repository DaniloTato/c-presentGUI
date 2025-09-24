# ------------------------
# Project settings
# ------------------------
target := a

source_dir  := src
include_dir := include
build_dir   := build

# ------------------------
# Sources and objects
# ------------------------
sources := $(shell find $(source_dir) -name '*.cpp')
headers := $(shell find $(include_dir) -name '*.hpp')
objs    := $(patsubst $(source_dir)/%.cpp,$(build_dir)/%.o,$(sources))

# ------------------------
# Compiler and flags
# ------------------------
CXX    := g++
CXXSTD := c++17

# Detect Homebrew installations
BREW_SFML := ./sfml

# Compiler flags
CXXFLAGS := -Wall -Wextra -std=$(CXXSTD) \
            -I$(include_dir) \
            -I$(BREW_SFML)/include \
			-DPROJECT_ROOT=\"$(PWD)\" \

LIB_SFML := -L$(BREW_SFML)/lib -lsfml-graphics -lsfml-window -lsfml-system -lcpresent

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

# Compile each source file into build/ directory
$(build_dir)/%.o: $(source_dir)/%.cpp | $(build_dir)
	@mkdir -p $(dir $@)
	@echo "Compiling $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

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