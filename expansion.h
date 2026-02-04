#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef int32_t i32;
typedef uint8_t u8;
typedef uint64_t u64;
typedef i32 b32;

#define KiB(n) ((u64)(n) << 10)
#define MiB(n) ((u64)(n) << 20)
#define GiB(n) ((u64)(n) << 30)

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/* ============================================================
   Dynamic Array(List)
   Expected layout:
     struct {
         Type *items;
         size_t count;
         size_t capacity;
     } xs;
     - see example.c
============================================================ */
#define list_append(xs, x)\
do{\
    if(xs.count >= xs.capacity){\
        if(xs.capacity == 0) xs.capacity = 256;\
        else xs.capacity *= 2;\
        xs.items = realloc(xs.items, xs.capacity*sizeof(*xs.items));\
    }\
    xs.items[xs.count++] = x;\
 } while(0)
#define ls_foreach(Type, it, da) for (Type *it = (da)->items; it < (da)->items + (da)->count; ++it)

typedef struct
{
    u8* str;
    size_t size;
} string;

#define STR_LIT(s) (string){ (u8*)(s), sizeof((s)) - 1}
#define STR_FMT(s8) (i32)(s8).size, (s8).str
/* #define sasprintf(write_to, ...) { \ */
/*  u8* tmp_string = (write_to); \ */
/*  asprintf(&(write_to), __VA_ARGS__); \ */
/*  free(tmp_string); \ */
/* } */

#define Fn_apply(type, fn, ...) { \
 void *stopper_for_apply = (int[]){0};                       \
 type **list_for_apply = (type*[]){__VA_ARGS__, stopper_for_apply}; \
 for (int i=0; list_for_apply[i] != stopper_for_apply; i++) \
 fn(list_for_apply[i]); \
}

#define multifree(...) Fn_apply(void, free, __VA_ARGS__);

typedef struct 
{
    size_t capacity;
    u64 pos;
} MemArena;

#define ARENA_BASE_POS (sizeof(MemArena))
#define ARENA_ALIGN (sizeof(void*))
#define ALIGN_UP_POW2(n, p) (((u64)(n) + ((u64)(p) -1)) & (~((u64)(p) - 1)))

MemArena* NewArena(size_t capacity);
void DestroyArena(MemArena* arena);
void* ArenaPush(MemArena* arena, size_t size, b32 nonZero);
void ArenaClear(MemArena* arena);
void ArenaPop(MemArena* arena, size_t size);
void ArenaPopTo(MemArena* arena, u64 pos);
#define ARENA_PUSH_STRUCT(arena, T) (T*)ArenaPush((arena), sizeof(T), false)
#define ARENA_PUSH_STRUCT_NZ(arena, T) (T*)ArenaPush((arena), sizeof(T), true)
#define ARENA_PUSH_ARRAY(arena, T, n) (T*)ArenaPush((arena), sizeof(T) * (n), false)
#define ARENA_PUSH_ARRAY_NZ(arena, T, n) (T*)ArenaPush((arena), sizeof(T) * (n), true)

#ifdef DOMAIN_EXPANSION
MemArena* NewArena(size_t capacity)
{
    MemArena* arena = (MemArena*)malloc(capacity);
    arena->capacity = capacity;
    arena->pos = ARENA_BASE_POS;
    return arena;
}

void DestroyArena(MemArena* arena)
{
    free(arena);
}

void* ArenaPush(MemArena* arena, size_t size, b32 nonZero)
{
    u64 posAligned = ALIGN_UP_POW2(arena->pos, ARENA_ALIGN);
    u64 newPos = posAligned + size;
    if(newPos > arena->capacity) return NULL;
    arena->pos = newPos;
    u8* out = (u8*)arena + posAligned;
    if(!nonZero)
        memset(out, 0, size);
    return out;
}

void ArenaPop(MemArena* arena, size_t size)
{
    size = MIN(size, arena->pos - ARENA_BASE_POS);
    arena->pos -= size;
}

void ArenaPopTo(MemArena* arena, u64 pos)
{
    u64 size = pos < arena->pos ? arena->pos - pos : 0;
    ArenaPop(arena, size);
}

void ArenaClear(MemArena* arena)
{
    ArenaPopTo(arena, ARENA_BASE_POS);
}
#endif
