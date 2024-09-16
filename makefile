CC     := g++
CFLAGS := -g -Wall -Wpedantic -Wpedantic -Wextra -Og -Iinclude

# cpp and header files from own project
# 2 (or 1?) levels of recursion
CPP_FILES := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
HEADERS   := $(wildcard include/*.hpp) $(wildcard include/*/*.hpp)

# packages from package manager
PACKAGES := sfml-all
PKG_LIBS := $(shell pkg-config --libs $(PACKAGES))
CFLAGS   += $(shell pkg-config --cflags $(PACKAGES))

# obj files. decided by cpp files, so last
OBJ_FILES := $(patsubst %.cpp,obj/%.o,$(CPP_FILES))

.PHONY: clean run

all: bin/main.out

run: bin/main.out
	./bin/main.out

clean:
	rm obj/* -rf
	rm bin/* -rf

obj/%.o: %.cpp $(HEADERS)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

bin/main.out: $(OBJ_FILES)
	$(CC) $(CFLAGS) $(PKG_LIBS) $^ -o $@