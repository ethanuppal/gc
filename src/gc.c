// Copyright (C) 2024 Ethan Uppal. All rights reserved.

#define GC_PRIVATE
#include "gc.h"
#undef GC_PRIVATE

#include <stdbool.h>  // bool
#include <stdlib.h>   // malloc, realloc

void* gc_malloc_aux(struct gc* gc, size_t size) {
    void* result = malloc(size);
#ifdef GC_STATS
    if (result) {
        gc->stats.auxillary_bytes += size;
    }
#else
    (void)gc;
#endif
    return result;
}

void* gc_malloc_object(struct gc* gc, size_t size) {
    void* result = malloc(size);
#ifdef GC_STATS
    if (result) {
        gc->stats.object_bytes += size;
    }
#else
    (void)gc;
#endif
    return result;
}

struct gc* gc_create(void) {
    struct gc* gc = malloc(sizeof(*gc));
    if (!gc) {
        return NULL;
    }

    gc->objects = NULL;

#ifdef GC_STATS
    gc->stats.object_bytes = 0;
    gc->stats.auxillary_bytes = sizeof(*gc);
#endif

    return gc;
}

void* gc_alloc(struct gc* gc, size_t size) {
    size = (size + 15ULL) & (-16ULL);

    gc_collect(gc);

    struct gc_node* new_head = gc_malloc_aux(gc, sizeof(*gc->objects));
    if (!new_head) {
        return NULL;
    }

    new_head->next = gc->objects;
    gc->objects = new_head;

    new_head->object = gc_malloc_object(gc, sizeof(*new_head->object) + size);
    if (!new_head->object) {
        return NULL;
    }

    return new_head->object->start;
}

void gc_collect(struct gc* gc) {
    (void)gc;
}

#ifdef GC_STATS

size_t gc_memory_usage(const struct gc* gc) {
    return gc->stats.object_bytes;
}

size_t gc_memory_overhead(const struct gc* gc) {
    return gc->stats.auxillary_bytes;
}

#endif
