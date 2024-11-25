// Copyright (C) 2024 Ethan Uppal. All rights reserved.

#pragma once

#include <stddef.h>   // size_t1
#include <stdbool.h>  // bool
#include <stdint.h>   // uint64_t

struct gc;

struct gc* gc_begin(void);

void* gc_alloc(struct gc* gc, size_t size);

#ifdef GC_PRIVATE

#ifdef __GNUC__
#define PACKED __attribute__((packed))
#else
#define PACKED
#endif

struct PACKED gc_meta {
    uint64_t tag;
    uint64_t size;
};

struct gc_object {
    struct gc_meta meta;
    char start[];
};

struct gc_node {
    struct gc_object* object;
    struct gc_node* next;
};

#ifdef GC_STATS
struct gc_stats {
    size_t object_bytes;
    size_t auxillary_bytes;
};
#endif

struct gc {
    struct gc_node* objects;
#ifdef GC_STATS
    struct gc_stats stats;
#endif
};

extern uint64_t get_rbp(void);
extern uint64_t get_rsp(void);

void gc_collect(struct gc* gc);

#ifdef GC_STATS
size_t gc_memory_usage(const struct gc* gc);

size_t gc_memory_overhead(const struct gc* gc);
#endif

#endif
