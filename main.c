#include <vfs.h>
#include <devfs.h>
#include <libc/hasht/hasht.h> 
#include <stdlib.h>
#include <libc/string.h>
#include <stdio.h>

int main(){

    init_vfs();

    //init_devfs();

    struct vfs_inode *node = calloc(sizeof(struct vfs_inode),1);

    struct vfs_inode *node1 = calloc(sizeof(struct vfs_inode),1);



    vfs_mkfile(vfs_get_root(),  node, "YO.txt");

    vfs_mkdir(vfs_get_root(), node1, "yo");

    vfs_get_node_from_path("/YO.txt");

    

    

    /*hasht* ht;
    hasht_init(&ht, 10);

    ht->push(ht, "haha", sizeof(struct vfs_inode), node, HT_PUSH_FLAG_REPLACE);

    ht->list_keys(ht);

    struct vfs_inode *n = (struct vfs_inode*)ht->get(ht, "haha");

    printf("%s\n", n->name);*/

    


    

    //print_vfs("/");

}