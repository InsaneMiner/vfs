#ifndef __VFS

#define __VFS

#include <stdint.h>
#include <stdbool.h>

#include <libc/dynlist/dynlist.h>

#define NAME_MAX_SIZE 125

enum type{
    NODE_TYPE_DIR,
    NODE_TYPE_FILE,
    NODE_TYPE_MOUNTPOINT,
};


struct vfs_inode;

struct vfs_ops{
    int (*read) (struct vfs_inode *, uint32_t, uint32_t, char *);
    int (*write) (struct vfs_inode *, uint32_t, uint32_t, char *);
    void (*open) (struct vfs_inode *, int32_t flags);
    void (*close) (struct vfs_inode *);
    int (*mkdir) (struct vfs_inode *, struct vfs_inode *);
    int (*mkfile) (struct vfs_inode *, struct vfs_inode *);
    int (*delfile) (struct vfs_inode*);
    int (*deldir) (struct vfs_inode*);
}__attribute__((packed));

struct device{
    uint32_t dev_id;
}__attribute__((packed));



struct filesystem{
    char name[200];
    struct vfs_inode * fs; 
    struct vfs_inode* (*mount)(struct filesystem*);
    int fs_flags;
    
};

struct mount_p{
    struct vfs_inode* root;
    struct filesystem* fs;
};


struct vfs_inode{
    char name[126];

    enum type type;


    int32_t uid;
    int32_t gid;

    bool open_flags;

    struct vfs_ops ops;

    struct vfs_inode *parent;
    struct vfs_inode **children;

    uint32_t children_count;

    struct vfs_inode* link; // for linking

    struct device dev;

    struct mount_p mp; //mount point

    struct vfs_super_block *sb;


};


void init_vfs();
void print_vfs(char *path);
struct vfs_inode* vfs_get_root();

void vfs_mkfile(struct vfs_inode* root, struct vfs_inode* new_node, char* name);


struct vfs_inode *vfs_get_node_from_path(char*path);

#endif

