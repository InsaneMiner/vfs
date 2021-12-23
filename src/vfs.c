#include <vfs.h>



#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

#include <libc/hasht/hasht.h>

#include <libc/string.h>

hasht * filesystems;

struct vfs_inode *root; // would be '/'





void init_vfs(){

    root = calloc(sizeof(struct vfs_inode),1);

    strcpy(root->name,"/");
}

struct vfs_inode* vfs_get_root(){
    return root;
}

void vfs_mkfile(struct vfs_inode* root, struct vfs_inode* new_node, char* name){
    root->children_count++;
    root->children = realloc(root->children, sizeof(struct vfs_inode) * root->children_count );

    

    strcpy(new_node->name, name);

    new_node->type = NODE_TYPE_FILE;



    //printf("%s\n",new_node->name);

    root->children[ root->children_count - 1 ] = new_node;


    if (root->ops.mkfile != NULL)
        root->ops.mkfile(root, new_node);

}

void vfs_mkdir(struct vfs_inode *root, struct vfs_inode *new_node, char*name){
    root->children_count++;
    root->children = realloc(root->children, sizeof(struct vfs_inode) * root->children_count );

    

    strcpy(new_node->name, name);

    new_node->type = NODE_TYPE_DIR;



    //printf("%s\n",new_node->name);

    root->children[ root->children_count - 1 ] = new_node;


    if (root->ops.mkdir != NULL)
        root->ops.mkdir(root, new_node);
}

int vfs_write(struct vfs_inode* __node, uint32_t __sz, uint32_t __offset, char *__buf){
    if (__node->ops.write != NULL){
        return __node->ops.write(__node,__sz, __offset, __buf);
    }
    return NULL;
    
}

struct vfs_inode *vfs_get_node_from_name(struct vfs_inode *__root, char *name){
    for (uint32_t c = 0; c < __root->children_count; c++){
        if (strcmp(__root->children[c], name) == 0){
            return __root->children[c];
        }
    }
    return NULL;
}

struct vfs_inode *vfs_get_node_from_path(char*path){
    if (strcmp(path,"/") == 0){
        return root;
    }

    char filen[NAME_MAX_SIZE] = {0};
    uint32_t noffset=0;

    uint32_t path_len = strlen(path);

    struct vfs_inode *cnode = root; // this is set to the root because root should be the start.

    if (path[0] != '/'){ // must have root
        return NULL;
    }


    struct string_array* tok_path = tokenize(path, '/');

    if(tok_path == NULL){
        return NULL;
    }
    else{
        

        for  (int d = 0; d <= tok_path->size-1; d++){

            cnode = vfs_get_node_from_name(cnode,tok_path->array[d]);

            if  (cnode == NULL){
                printf("dosiero aux dosierujo ne ekzistas!");
                return NULL;
            }

            if ( d != ( tok_path->size - 1)){
                if (cnode->type != NODE_TYPE_DIR || cnode->type != NODE_TYPE_MOUNTPOINT){
                    printf("must be a direcotory!\n");
                    return NULL;
                }
            }
            
            
        }
        return cnode;

    }


    return 0;
}


void print_vfs(char *path){
    struct vfs_inode* node = vfs_get_node_from_path(path);

    printf("\t");

    for (uint32_t c=0; c < node->children_count; c++){
        printf("%s\t\t", node->children[c]->name);
    }
    printf("\n");

}

bool vfs_register_filesystem(struct filesystem *fs){

    return filesystems->push(filesystems, fs->name, sizeof(struct filesystem), fs, HT_PUSH_FLAG_KEEP);
}

bool vfs_unregister_filesystem(struct filesystem* fs){

    return filesystems->pop(filesystems, fs->name);
    
}