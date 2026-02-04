#include "../expansion.h"
#include <stdio.h>

int main()
{
    string text = STR_LIT("String Example");
    printf("%.*s", STR_FMT(text));
    return 0;
}
