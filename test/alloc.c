// Copyright (C) 2024 Ethan Uppal. All rights reserved.

#include "../deps/simple-test/simple_test.h"
#include "../src/gc.h"
#include <string.h>

void test_main(void) {
    struct gc* gc = gc_create();
    assert_true(!!gc);
    char* str = gc_alloc(gc, 40);
    strcpy(str, "foo");
    assert_true(strcmp(str, "foo") == 0);

    (void)test_assert_equal;  // for -Werror
}
