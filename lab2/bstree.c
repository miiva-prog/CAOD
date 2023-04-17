#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstree.h"
 
bstree* bstree_create(int value,char *key)
{
    bstree *node = NULL;

    node = malloc(sizeof(*node));

    if(node != NULL){
        node->key = key;
        node->value = value;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

void bstree_add(bstree *tree,int value,char *key)
{
    if(tree == NULL)
        return ;

    bstree *node = NULL,*parent = NULL;

    while(tree != NULL){
        parent = tree;
        if(strcmp(key,tree->key) > 0){
            tree = tree->right;
        }else if(strcmp(key,tree->key) < 0){
            tree = tree->left;
        }else{
            return ;
        }
    }

    node = bstree_create(value,key);

    if(node == NULL)
        return ;

    if(strcmp(key,parent->key) < 0){
        parent->left = node;
    }else if(strcmp(key,parent->key) > 0){
        parent->right = node;
    }
}

bstree* bstree_lookup(bstree *tree,char *key)
{
    while(tree != NULL){
        if(strcmp(key,tree->key) == 0){
            return tree;
        }else if(strcmp(key,tree->key) > 0){
            tree = tree->right;
        }else if(strcmp(key,tree->key) < 0){
            tree = tree->left;
        }
    }
    return tree;
}

bstree* bstree_min(bstree *tree)
{
    while(tree->left != NULL){
        tree = tree->left;
    }
    return tree;
}

bstree* bstree_max(bstree *tree)
{
    while(tree->right != NULL){
        tree = tree->right;
    }
    return tree;
}

void print_bstree(bstree *tree,int prob)
{
    if(tree != NULL){
        print_bstree(tree->left,prob + 2);

        for(int n = 0;n < prob;n++){
            printf("\t");
        }
 
        printf("%s\n",tree->key);
        print_bstree(tree->right,prob + 2);
    }
}

void replace(bstree *parent,bstree *node,bstree *child)
{
    if(parent != NULL){
        if(parent->right == node)
            parent->right = child;
        else
            parent->left = child;
    }
}

bstree* delete(bstree *tree,bstree *node,bstree *parent)
{
    if(node == NULL)
        return tree;

    if(node->left == NULL){
        replace(parent,node,node->right);
        if(parent == NULL)
            tree = node->right;
    }else if(node->right == NULL){
        replace(parent,node,node->left);
        if(parent == NULL)
            tree = node->left;
    }else{
        bstree *rig = node->right,*parent_rig = rig;
        while(rig->left != NULL){
            parent_rig = rig;
            rig = rig->left;
        }
        replace(parent,node,rig);
        if(parent == NULL)
            tree = rig;
        
        if(node->right != rig){
            parent_rig->left = rig->right;
            rig->left = node->left;
            rig->right = node->right;
        }else{
            rig->left = node->left;
        }
    }
    free(node);
    return tree;
}

bstree *bstree_delete(bstree *tree,char *key)
{
    int test;

    if(tree == NULL)
        return NULL;
    
    bstree *parent = NULL;
    bstree *node = tree;

    while(node != NULL && (test = strcmp(node->key,key) != 0)){
        parent = node;
        if(strcmp(key, node->key) > 0)
            node = node->right;
        else 
            node = node->left;
    }
    return delete(tree, node, parent);
}
 
void bstree_delete_all(bstree *tree)
{
    if(tree != NULL){
        bstree_delete_all(tree->left);
        bstree_delete_all(tree->right);
        free(tree);
    }
}