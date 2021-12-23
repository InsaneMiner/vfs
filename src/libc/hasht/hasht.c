#include <libc/hasht/hasht.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static unsigned int hasht_c_hash(char* key)
{
	unsigned int hash = 5381;
	int c;
	while ((c = *key++) != 0)
		hash = ((hash << 5) + hash) + c;

	return hash;
}

static bool push(hasht *v, char *key, int data_sz, void*data, int flag){
    if (data == NULL || v == NULL){
        return false;
    }

    void *ndata = malloc(data_sz);

    if (ndata ==  NULL){
        return false;
    }

    memcpy(ndata, data, data_sz);

    unsigned int index = hasht_c_hash(key) % v->capacity;

    hasht_node * node = v->table[index];

    while(node != NULL) //  we must check if  key exists
	{
        
		if(!strcmp(node->key, key))
		{
            if  (flag == HT_PUSH_FLAG_REPLACE){
                free(node->value); // delete old data

			    node->value = ndata; // replace with new data
                
                return true;

            }else if (flag  ==  HT_PUSH_FLAG_KEEP){
                return false;
            }
		}
		node = node->next;
	}

    node = malloc( sizeof(hasht_node) );

    if (node != NULL){ //  add new node

        node->key = malloc(strlen(key)+1);
        strcpy(node->key, key);
        node->value = ndata;

        node->next = v->table[index];
	    v->table[index] = node;
	    v->node_num++;

        return true;

    }
    else{
        return false;
    }
    
}

static void* get(hasht* v, char* key)
{
	unsigned int index = hasht_c_hash(key) % v->capacity;
	hasht_node* n = v->table[index];
	while(n != NULL)
	{
		if(!strcmp(n->key, key))
			return n->value;
		n = n->next;
	}
	return NULL;
}

static bool pop(hasht *v, char* key){
    unsigned int h = hasht_c_hash(key) % v->capacity;
	hasht_node* e = v->table[h];
	hasht_node* prev = NULL;

	while(e != NULL)
	{
		if(!strcmp(e->key, key))
		{
			free(e->value);
			if(prev != NULL)
				prev->next = e->next;
			else
				v->table[h] = e->next;

			free(e);

			e = NULL;

			v->node_num--;

			return true;
		}
		prev = e;
		e = e->next;
	}
	return false;
}
static void list_keys(hasht*v){
	int i = v->capacity;
	while(--i >= 0)
	{
		hasht_node* e = v->table[i];
		while(e)
		{
            printf("key: %s\n", e->key);
			e = e->next;
		}
	}
}



void hasht_init(hasht **v, unsigned int capacity){
    *v = malloc(sizeof(hasht));

    if(!(*v))
		return;
	if(( (*v)->table = malloc(capacity*sizeof(hasht_node*))) == NULL)
	{
		free((*v)->table);
		return;
	}
	(*v)->capacity = capacity;
	(*v)->node_num = 0;

    (*v)->push = push;
    (*v)->get  = get;
    (*v)->pop = pop;
    (*v)->list_keys = list_keys;

	unsigned int i;
	for(i = 0; i < capacity; i++)
		(*v)->table[i] = NULL;

}


