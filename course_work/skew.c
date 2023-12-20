#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include<sys/time.h>

struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct SkewHeap
{
    struct TreeNode *root;
};

struct SkewHeap* create_skew();

struct TreeNode *merge_node(struct TreeNode *n1,struct TreeNode *n2);

void swap_child(struct TreeNode *parent);

void add_node(struct SkewHeap *tree,int data);

void merge_tree(struct SkewHeap *tree1,struct SkewHeap *tree2);

void delete_min(struct SkewHeap *tree);

void min_element(struct SkewHeap *tree);

void print_skew(struct TreeNode *tree,int prob);

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

int getrand(int min,int max)
{
    return (double)rand()/(RAND_MAX + 1.0) * (max - min) + min;
}

int main()
{
    struct SkewHeap *tree1 = create_skew();

    add_node(tree1,15);
    add_node(tree1,8);
    add_node(tree1,10);
    add_node(tree1,5);
    add_node(tree1,2);
    add_node(tree1,3);
    add_node(tree1,21);
    printf("\nTree 1\n");
    print_skew(tree1->root,0);

    struct SkewHeap *tree2 = create_skew();

    add_node(tree2,4);
    add_node(tree2,20);
    add_node(tree2,13);
    add_node(tree2,16);
    add_node(tree2,18);
    add_node(tree2,9);
    printf("\n\n\nTree 2\n");
    print_skew(tree2->root,0);

    printf("\nMerge\n");
    merge_tree(tree1,tree2);
    print_skew(tree1->root,0);

    printf("\n\nDelete Min");
    min_element(tree1);
    delete_min(tree1);
    print_skew(tree1->root,0);

    // srand(time(NULL));

    // struct SkewHeap *tree = create_skew(); 
    // double time_add = wtime();

    // for(int n = 1;n < 1000000;n++){
    //     add_node(tree,n + 1);

    //     if(n % 50000 == 0){
    //         time_add = wtime() - time_add;
    //         printf("time -> %.6lf | count elements - > %d\n",time_add,n);
    //         time_add = wtime();
    //     }
    // }
    
    return 0;
}

struct SkewHeap* create_skew()
{
    struct SkewHeap *tree = (struct SkewHeap*)malloc(sizeof(struct SkewHeap));

    if(tree != NULL)
        tree->root = NULL;
    else
        return NULL;

    return tree;
}

void swap_child(struct TreeNode *parent)
{
    if(parent != NULL){
        struct TreeNode * temp = parent->left;
        parent->left = parent->right;
        parent->right = temp;
    }
}

struct TreeNode* merge_node(struct TreeNode *n1,struct TreeNode *n2)
{
    if(n1 == NULL)
        return n2;
    
    if(n2 == NULL)
        return n1;

    if(n1->data < n2->data){
        struct TreeNode *temp = n1->right;

        n1->right = n1->left;
        n1->left = merge_node(n2,temp);

        return n1; 
    }else{
        return merge_node(n2,n1);
    }
}

void add_node(struct SkewHeap *tree,int data)
{
    struct TreeNode *node = (struct TreeNode*)malloc(sizeof(struct TreeNode));

    if(node != NULL){
        node->data = data;
        node->left = NULL;
        node->right = NULL;
    }else{
        return;
    }

    tree->root = merge_node(node,tree->root);
}

void merge_tree(struct SkewHeap *tree1,struct SkewHeap *tree2)
{
    tree1->root = merge_node(tree1->root,tree2->root);
    tree2->root = NULL;
}

void delete_min(struct SkewHeap *tree)
{
    if(tree->root != NULL)
        tree->root = merge_node(tree->root->left,tree->root->right);
}

void min_element(struct SkewHeap *tree)
{
    if(tree->root != NULL)
        printf("\nMin Element -> %d\n",tree->root->data);
}

void print_skew(struct TreeNode *tree,int prob)
{
    if(tree != NULL){
        print_skew(tree->left,prob + 2);

        for(int n = 0;n < prob;n++)
            printf("\t");
 
        printf("%d\n",tree->data);
        print_skew(tree->right,prob + 2);
    }
}