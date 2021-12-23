#include <devfs.h>

#include <vfs.h>

#include <stdlib.h>

struct vfs_inode * device_node;


void init_devfs(){
    device_node = calloc(sizeof(struct vfs_inode),1);

    vfs_mkfile(vfs_get_root(), device_node, "devices");
}

void devfs_mkfile(struct vfs_inode *root, struct vfs_inode *){

}