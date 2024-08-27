# Copyright (C) 2024 Ethan Uppal. All rights reserved.

SRCDIR		:= src
TESTDIR		:= test

CC			:= $(shell which gcc || which clang)
CFLAGS		:= -std=c99 -pedantic -Wall -Wextra -Werror -I $(SRCDIR)

NASM		:= nasm

C_SRC		:= $(shell find $(SRCDIR) -type f -name "*.c")
ASM_SRC		:= $(shell find $(SRCDIR) -type f -name "*.asm")
OBJ			:= $(C_SRC:.c=.o) $(ASM_SRC:.asm=.o)

BUILT_LIB 	:= gc.so

ifeq ($(shell uname), Darwin)
AR 			:= /usr/bin/libtool
ARFL 		:= -static
NASMFL		:= -f macho64
INSTNASM	:= brew install nasm
else
AR 			:= ar
ARFL 		:= rcs $@ $^
NASMFL		:= -f elf64
endif

TESTS		:= $(shell find $(TESTDIR) -type f -name "*.c")

## ----------------------------------------------------
## Build system for this garbage collection runtime.
## Copyright (C) 2024 Ethan Uppal. All rights reserved.
## ----------------------------------------------------

.PHONY: build
build: deps	## Builds the static library.
	@make $(BUILT_LIB)

.PHONY: clean
clean:		## Removes build files
	rm -f $(OBJ)

.PHONY: deps
deps:		## Installs dependencies.
	if [ ! -d deps/simple-test ]; then \
		git submodule add https://github.com/ethanuppal/simple-test deps/simple-test; \
	fi
	git submodule update --recursive --remote
	$(INSTNASM)

.PHONY: test
test: build		## Runs tests
	@make _test

# https://stackoverflow.com/questions/8889035/how-to-document-a-makefile
help:     	## Shows this help.
	@sed -ne '/@sed/!s/## //p' $(MAKEFILE_LIST)

.PHONY: $(BUILT_LIB)
$(BUILT_LIB): $(OBJ)
	$(AR) $(ARFL) -o $@ $^

.PHONY: _test
_test: $(BUILT_LIB) $(TESTS)
	@for test in $(TESTS); do \
		$(CC) $(CFLAGS) -DTEST -o _temp $$test $<; \
		echo 'Running tests...'; \
		./_temp; \
		rm -f ./_temp; \
	done

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

%.o: %.asm
	$(NASM) $(NASMFL) -o $@ $^
