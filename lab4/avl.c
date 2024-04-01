#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

typedef struct node{
    int key;
    char *value;
    struct node *left;
    struct node *right;
    int height;
}avltree;

double wtime();

int get_height(avltree *n);

avltree* avltree_create(int key);

int max(int a,int b);

int get_balance_factor(avltree *n);

avltree* right_rotate(avltree *y);

avltree* left_rotate(avltree *x);

avltree *avltree_add(avltree *node,int key);

avltree* avltree_lookup(avltree *tree,int key);

avltree *avltree_delete_node(avltree *root,int key);

void avltree_print(avltree *root,int prob);

void avltree_free(avltree *tree);

avltree* avltree_min(avltree *tree);

int main()
{
    srand(time(NULL));

    avltree *root = avltree_create(0);

    for(int i = 1;i <= 990000 + 1;i++){
        root = avltree_add(root,i);
        if((i >= 30000) && (i % 30000 == 0)){
            double time = 0;
            for(int k = 0;k < 100;k++){
                int num = rand() % i;

                double time_avltree_lookup = wtime();
                avltree *avl_lookup = avltree_lookup(root,num);
                time_avltree_lookup = wtime() - time_avltree_lookup;

                time += time_avltree_lookup;
            }
            printf("%d %lf\n",i,time);
        }
    }

    avltree_free(root);

    return 0;
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int get_height(avltree *n)
{
    if(n == NULL)
        return 0;

    return n->height;
}

avltree* avltree_create(int key)
{
    avltree *node = (avltree *)malloc(sizeof(avltree));

    if (node == NULL)
        return NULL;
    
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

int max(int a,int b)
{
    if(a > b)
        return a;
    else
        return b;
}

int get_balance_factor(avltree *n)
{
    if(n == NULL) 
        return 0;
    
    return get_height(n->left) - get_height(n->right);
}

avltree* right_rotate(avltree *y)
{
    avltree *x = y->left;
    avltree *T2 = x->right;

    x->right = y;
    y->left = T2;

    x->height = max(get_height(x->right),get_height(x->left)) + 1;
    y->height = max(get_height(y->right),get_height(y->left)) + 1;

    return x;
}

avltree* left_rotate(avltree *x)
{
    avltree *y = x->right;
    avltree *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(get_height(x->right),get_height(x->left)) + 1;
    y->height = max(get_height(y->right),get_height(y->left)) + 1;

    return y;
}

avltree *avltree_add(avltree *node,int key)
{
    if(node == NULL)
        return avltree_create(key);

    if(key < node->key)
        node->left = avltree_add(node->left, key);
    else if(key > node->key)
        node->right = avltree_add(node->right, key);

    node->height = 1 + max(get_height(node->left), get_height(node->right));

    int bf = get_balance_factor(node);

    if(bf == 2 && key < node->left->key)
        return right_rotate(node);

    if(bf == -2 && key > node->right->key)
        return left_rotate(node);

    if(bf == 2 && key > node->left->key){
        node->left = left_rotate(node->left);
        return right_rotate(node);
    }

    if(bf == -2 && key < node->right->key){
        node->right = right_rotate(node->right);
        return left_rotate(node);
    }

    return node;
}

avltree* avltree_lookup(avltree *tree,int key)
{
    if(tree == NULL)
        return NULL;

    while(tree != NULL){
        if(key == tree->key){
            return tree;
        }else if(key < tree->key){
            tree = tree->left;
        }else{
            tree = tree->right;
        }
    }  
    
    return NULL;
}

avltree* avltree_delete_node(avltree *root,int key) 
{
    if(root == NULL)
        return root;

    if(key < root->key){
        root->left = avltree_delete_node(root->left,key);
    }else if(key > root->key){
        root->right = avltree_delete_node(root->right,key);
    }else{ 
        if((root->left == NULL) || (root->right == NULL)){
            avltree *temp = root->left ? root->left : root->right;
            if(temp == NULL){
                temp = root;
                root = NULL;
            }else{
                *root = *temp;
            }

            free(temp);
        }else{
            avltree *temp = avltree_min(root->right);

            root->key = temp->key;
            root->right = avltree_delete_node(root->right, temp->key);
        }
    }

    if(root == NULL)
        return NULL;

    root->height = 1 + max(get_height(root->left),get_height(root->right));

    int balance = get_balance_factor(root);

    if(balance > 1 && get_balance_factor(root->left) >= 0) 
        return right_rotate(root);

    if(balance > 1 && get_balance_factor(root->left) < 0){
        root->left = left_rotate(root->left);
        return right_rotate(root);
    }

    if(balance < -1 && get_balance_factor(root->right) <= 0)
        return left_rotate(root);

    if(balance < -1 && get_balance_factor(root->right) > 0){
        root->right = right_rotate(root->right);
        return left_rotate(root);
    }

    return root;
}

void avltree_print(avltree *root,int prob)
{
    if(root == NULL)
        return;

    prob += 5;

    avltree_print(root->right,prob);
    printf("\n");

    for(int i = 5;i < prob;i++)
        printf(" ");

    printf("%d\n",root->key);
    avltree_print(root->left,prob);
}

void avltree_free(avltree *tree)
{
    if(tree != NULL){
        avltree_free(tree->right);
        avltree_free(tree->left);
        free(tree);
    }
}

avltree* avltree_min(avltree *tree)
{
    while(tree->left != NULL)
        tree = tree->left;
    
    return tree;
}