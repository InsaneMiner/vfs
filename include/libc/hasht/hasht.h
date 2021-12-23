#ifndef __HASHT_H

#define __HASHT_H

#define HT_PUSH_FLAG_REPLACE 1
#define HT_PUSH_FLAG_KEEP 2

#include <stdbool.h>



typedef struct hasht_node{
    char *key;
    void *value;

    struct hasht_node *next;

}hasht_node;

typedef struct hasht{
    hasht_node** table;
    unsigned int node_num;
    unsigned int capacity;
    bool (*push)(struct hasht*, char*, int, void*, int);
    void* (*get)(struct hasht*, char*);
    bool (*pop)(struct hasht*,char*);
    void (*list_keys)(struct hasht*);
}hasht;


void hasht_init(hasht **v, unsigned int capacity);


#endif

