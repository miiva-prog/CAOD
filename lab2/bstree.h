typedef struct{
    char *key;
    int value;
    struct bstree *left;
    struct bstree *right;
}bstree;

bstree* bstree_create(int value,char *key);

void bstree_add(bstree *tree,int value,char *key);

bstree* bstree_lookup(bstree *tree,char *key);

bstree* bstree_min(bstree *tree);
 
bstree* bstree_max(bstree *tree);

void print_bstree(bstree *tree,int prob);

void replace(bstree *parent,bstree *node,bstree *child);

bstree* delete(bstree *tree,bstree *node,bstree *parent);

bstree* bstree_delete(bstree *tree,char *key);
 
void bstree_delete_all(bstree *tree);