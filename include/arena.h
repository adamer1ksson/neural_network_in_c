#pragma once
#include "base.h"
#include "stdbool.h"

#define ARENA_BASE_POS (sizeof(mem_arena))
#define ARENA_ALIGN (sizeof(void*))
#define ALIGN_UP(x, a) (((x) + ((a) - 1)) & ~((a) - 1))

#define PUSH_STRUCT(arena, T) (arena_push((arena), (u64)( sizeof(T) ), true))
#define PUSH_N_STRUCTS(arena, T, n) (arena_push((arena), (u64)( sizeof(T) * (n)), true))
#define PUSH_STRUCT_NZ(arena, T) (arena_push((arena),(u64)( sizeof(T) ), false))
#define PUSH_N_STRUCTS_NZ(arena, T, n) (arena_push((arena), (u64)( sizeof(T) * (n)), false))

#define POP_STRUCT(arena, T) (arena_pop((arena), (u64)( sizeof(T) )))
#define POP_N_STRUCTS(arena, T, n) (arena_pop((arena), ( sizeof(T) * (n))))

typedef struct {
    u64 capacity;
    u64 pos; 
} mem_arena;

mem_arena* arena_create(u64 capacity);
void arena_destroy(mem_arena* arena);
void* arena_push(mem_arena* arena, u64 size, bool set_zero);
void arena_pop(mem_arena* arena, u64 size);
