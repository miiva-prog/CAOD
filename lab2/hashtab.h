#define HASHTAB_SIZE 200003
#define hash_mul 31

typedef struct{
    int value;
    char *key;
    struct listnode *next;
}listnode;

void hashtab_init(listnode **hashtab);

unsigned int hashtab_hash(char *key);

unsigned int ELFHash(char *s);

void hashtab_add(listnode **hashtab,char *key,int value);

void ELF_add(listnode **hashtab,char *key,int value);

listnode* ELFHash_lookup(listnode **hashtab,char *key);

listnode* hashtab_lookup(listnode **hashtab,char *key);

void hashtab_delete(listnode **hashtab,char *key);
 
listnode* hashtab_delete_all(listnode **hashtab);