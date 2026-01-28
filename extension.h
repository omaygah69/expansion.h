#pragma once
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int32_t i32;
typedef uint8_t u8;
typedef uint64_t u64;
typedef i32 b32;

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
#define sasprintf(write_to, ...) { \
 u8* tmp_string = (write_to); \
 asprintf(&(write_to), __VA_ARGS__); \
 free(tmp_string); \
}

#define Fn_apply(type, fn, ...) { \
 void *stopper_for_apply = (int[]){0};                       \
 type **list_for_apply = (type*[]){__VA_ARGS__, stopper_for_apply}; \
 for (int i=0; list_for_apply[i] != stopper_for_apply; i++) \
 fn(list_for_apply[i]); \
}

#define multifree(...) Fn_apply(void, free, __VA_ARGS__);
