#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtab.h"

unsigned int colisias = 0;

void hashtab_init(listnode **hashtab)
{
    for(int n = 0;n < HASHTAB_SIZE;n++)
        hashtab[n] = NULL;
}

unsigned int hashtab_hash(char *key)
{
    unsigned int h = 0;

    while(*key)
        h = h * hash_mul + (unsigned int)*key++; 

    return h % HASHTAB_SIZE;
}
  
unsigned int ELFHash(char *s)
{
    unsigned int h = 0,g;

    while(*s){
        h = (h << 4) + (unsigned int)*s++;
        g = h & 0xF0000000L;

        if(g)
            h ^= g >> 24;
        h &= ~g;
    }
    return h % HASHTAB_SIZE;
}

void hashtab_add(listnode **hashtab,char *key,int value)
{
    listnode *node;
    int index = hashtab_hash(key);

    node = malloc(sizeof(*node));

    if(hashtab[index] != NULL){
        colisias++;
        for(node = hashtab[index];node != NULL;node = node->next)
            if(strcmp(key,node->key) == 0)
                return ;
    }
    
    if(node != NULL){
        node->key = key;
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}

void ELF_add(listnode **hashtab,char *key,int value)
{
    listnode *node;
    int index = ELFHash(key);

    node = malloc(sizeof(*node));

    if(hashtab[index] != NULL)
        colisias++;

    if(node != NULL){
        node->key = key;
        node->value = value;
        node->next = hashtab[index];
        hashtab[index] = node;
    }
}

listnode* ELFHash_lookup(listnode **hashtab,char *key)
{
    listnode *node;
    int index = ELFHash(key);

    for(node = hashtab[index];node != NULL;node = node->next){
        if(0 == strcmp(node->key,key))
            return node;
    }
    return NULL;
}

listnode* hashtab_lookup(listnode **hashtab,char *key)
{
    listnode *node;
    int index = hashtab_hash(key);

    for(node = hashtab[index];node != NULL;node = node->next){
        if(0 == strcmp(node->key,key))
            return node;
    }
    return NULL;
}

void hashtab_delete(listnode **hashtab,char *key)
{
    listnode *node,*prev = NULL;
    int index = hashtab_hash(key);

    for(node = hashtab[index];node != NULL;node = node->next){
        if(0 == strcmp(node->key,key)){
            if(prev == NULL){
                hashtab[index] = node->next;
            }else{
                prev->next = node->next;
            }
            free(node);
            return;
        }
        prev = node;
    }
}

listnode* hashtab_delete_all(listnode **hashtab)
{
    for(int n = 0;n < HASHTAB_SIZE;n++){
        if(hashtab[n] != NULL){
            hashtab[n]->key = NULL;
            hashtab[n]->value = NULL;
        }
    }
    return hashtab;
}