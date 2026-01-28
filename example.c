#include "extension.h"
#include <stdio.h>

// define a struct list
typedef struct
{
    i32* items;
    size_t count;
    size_t capacity;
} ls_i32;

// you can reuse this for any type by just replacing type of the items
typedef struct
{
    string* items;
    size_t count;
    size_t capacity;
} ls_s8;

int main()
{
    ls_i32 lsi = {0};
    list_append(lsi, (i32)8);
    list_append(lsi, (i32)9);
    printf("List of int32:\n");
    ls_foreach(i32, it, &lsi){
        // foreach loop (type, item, collection)
        printf("%i\n", *it);
    }
    
    string text = STR_LIT("List of Strings:");
    string bro = STR_LIT("Friend");
    ls_s8 lstext = {0};
    printf("%.*s\n", STR_FMT(text));
    list_append(lstext, STR_LIT("Hello"));
    list_append(lstext, STR_LIT("my"));
    list_append(lstext, STR_LIT(bro.str));
    ls_foreach(string, ss, &lstext){
        // you can get the index by: i = it - da.items (see header)
        i32 i = ss - lstext.items;
        printf("string[%i] %.*s\n", i, STR_FMT(*ss));
    }    

    multifree(lsi.items, lstext.items);
    return 0;
}
