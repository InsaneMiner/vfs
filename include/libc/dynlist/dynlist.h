#ifndef __DYBNLIST_HEADER__
#define __DYBNLIST_HEADER__



#include <stdlib.h>
#include <string.h>



#define DL_INIT_CAPACITY 6
#define UNDEFINE  -1
#define SUCCESS 0



typedef struct dl
{
    void **items;
    int capacity;
    int total;
} dl_t;



typedef struct sDynlist dynlist;
struct sDynlist
{
    dl_t dl;
    int (*total)(dynlist *);
    int (*resize)(dynlist *, int);
    int (*push)(dynlist *, int, void *);
    int (*set)(dynlist *, int,int, void *);
    void *(*get)(dynlist *, int);
    int (*pop)(dynlist *, int);
    int (*free)(dynlist *);
};

extern void dl_init(dynlist **);

                            

#define ADD_DYNLIST(size, data, list) list->push(list, sizeof(size), data);



#endif