#define DOMAIN_EXPANSION
#include <stdio.h>
#include "../expansion.h"


int main(void)
{
    MemArena* arena = NewArena(KiB(32));
    string fromc = STR_LIT("Hello from C\n");
    printf("%.*s\n", STR_FMT(fromc));
    string ss = ArenaStringAppend(arena,
        STR_LIT("Hello, "),
        STR_LIT("World!")
    );

    if (ss.str)
        printf("%.*s\n", STR_FMT(ss));

    DestroyArena(arena);
    return 0;
}
