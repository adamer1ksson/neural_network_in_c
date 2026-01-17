#include "stdio.h"
#include "stddef.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"

#include "../include/arena.h"

mem_arena* arena_create(u64 capacity) {
    if (capacity <= ARENA_BASE_POS) {
        fprintf(stderr, "Arena has too low capacity.\n");
        exit(EXIT_FAILURE);
    }
    mem_arena* arena = malloc((size_t)capacity);
    if (!arena) {
        perror("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
    arena->capacity = capacity;
    arena->pos = (u64)ARENA_BASE_POS;

    return arena;
}

void arena_destroy(mem_arena* arena) {
    free(arena);
}

void* arena_push(mem_arena* arena, u64 size, bool set_zero) {
    u64 pos_aligned = ALIGN_UP(arena->pos, ARENA_ALIGN);
    u64 new_pos = pos_aligned + size;
    if (new_pos > arena->capacity) {
        fprintf(stderr, "Max capacity overflowed.\n");
        return NULL;
    }
    arena->pos = new_pos;
    u8* out = (u8*)arena + pos_aligned;
    if (set_zero) {
        memset(out, 0, (size_t)size);
    }
    return out;
}

void arena_pop(mem_arena* arena, u64 size) {
    i64 new_pos = arena->pos - size;
    if (new_pos < 0) {
        fprintf(stderr, "Cannot pop more than capacity.\n");
        new_pos = 0;
    }
    arena->pos = new_pos;
}


