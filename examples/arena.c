#define DOMAIN_EXPANSION
#include "../expansion.h"
#include <stdio.h>

typedef struct {
    i32 x;
    i32 y;
} Vector2;

int main()
{
    MemArena* arena = NewArena(MiB(3));
    Vector2* v = ARENA_PUSH_STRUCT(arena, Vector2);
    v->x = 6;
    v->y = 7;

    Vector2 *points = ARENA_PUSH_ARRAY(arena, Vector2, 3);
    for (i32 i = 0; i < 3; i++) {
        points[i].x = i;
        points[i].y = i * 2;
    }

    printf("a = (%d, %d)\n", v->x, v->y);
    printf("points[2] = (%d, %d)\n", points[2].x, points[2].y);
    
    DestroyArena(arena);
}
