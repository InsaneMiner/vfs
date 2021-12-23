#pragma once

struct string_array{
    char**array;
    int size;
};


struct string_array* tokenize(char *str, char tok);