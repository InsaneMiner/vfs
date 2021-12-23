#include <libc/string.h>
#include <stdio.h>
#include <string.h>

static int count_amount_of_tok(char*str,char tok){

    int size = 0;

    for (int i = 0; i < strlen(str);i++){
        if  (str[i] == tok){
            size++;
        }
    }
    return size;
}

struct string_array* tokenize(char *str, char tok){
    int size = 0;

    struct string_array* array = calloc(sizeof(struct string_array),1);
    int str_size = strlen(str);
    int start_pos = 0;
    int string_size;
    size = count_amount_of_tok(str,tok);
    if  (size == 0){
        return NULL;
    }
    array->array = calloc(sizeof(char*)*size,1);

    for (int i = 0; i <= str_size;i++){
        if  (str[i] == tok || i == str_size){

            if (string_size == 0){
                start_pos++;
                continue;
            }
            array->array[array->size] = calloc(string_size+1,1);
            strncpy(array->array[array->size], ( str + start_pos ), string_size) ; 
            start_pos = start_pos + string_size + 1;
            string_size = 0;
            array->size++;
        }
        else{
            string_size++;
        }
    }
    return array;
}