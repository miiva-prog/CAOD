#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "bstree.h"
#include "hashtab.h"
 
int getrand(int min,int max)
{
    return (double)rand()/(RAND_MAX + 1.0) * (max - min) + min;
}

double wtime()
{
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

listnode *hashtab[HASHTAB_SIZE];
listnode *hashtab_ELF[HASHTAB_SIZE];

int main()
{
    bstree *tree;
    hashtab_init(hashtab);
    double time_bstree,time_hashtab;
    unsigned int colisias = 0;
    FILE *file = fopen("random words.txt","r");

    tree = bstree_create(100000,"root");

    /*experiment 1*/

    printf("experiment 1\n\n");
    printf("bstree\n");

    for(int size = 1;size <= 200000;size++){
        char word[20];

        fgets(word,20,file);
        bstree_add(tree,getrand(0,size + 1),word);

        if(size % 10000 == 0){
            bstree *node;

            time_bstree = wtime();
            for(int n = 0;n < size * 1000;n++){
                node = bstree_lookup(tree,word);
            }
            time_bstree = wtime() - time_bstree;

            printf("size - %d  time - %.6lf\n",size,time_bstree);
        }
    }

    bstree_delete_all(tree);

    printf("\nhashtab\n");

    for(int size = 1;size <= 200000;size++){
        char word[20];

        fgets(word,20,file);
        hashtab_add(hashtab,word,getrand(0,size));

        if(size % 10000 == 0){
            listnode *node;

            time_hashtab = wtime();
            for(int n = 0;n < size * 1000;n++){
                node = hashtab_lookup(hashtab,word);
            }
            time_hashtab = wtime() - time_hashtab;

            printf("size - %d  time - %.6lf\n",size,time_hashtab);
        }
    }

    hashtab_delete_all(hashtab);

    /*experiment 2*/

    // printf("experiment 2\n\n");
    // printf("bstree\n");

    // time_bstree = wtime();

    // for(int size = 1;size <= 200000;size++){
    //     char word[20];

    //     fgets(word,20,file);
    //     bstree_add(tree,getrand(0,size + 1),word);

    //     if(size % 10000 == 0){
    //         time_bstree = wtime() - time_bstree;
    //         printf("size - %d  time - %.6lf\n",size,time_bstree);
    //         time_bstree = wtime();
    //     }

    // }

    // printf("\nhashtab\n");
    // time_hashtab = wtime();

    // for(int size = 1;size <= 200000;size++){
    //     char word[20];

    //     fgets(word,20,file);
    //     hashtab_add(hashtab,word,getrand(0,size));

    //     if(size % 10000 == 0){
    //         time_hashtab = wtime() - time_hashtab;
    //         printf("size - %d  time - %.6lf\n",size,time_hashtab);
    //         time_hashtab = wtime();
    //     }
    // }

    /*experiment 6*/

    // printf("experiment 6\n");
    // printf("\nhashtab\n");

    // for(int size = 1;size <= 200000;size++){
    //     char word[20];

    //     fgets(word,20,file);
    //     hashtab_add(hashtab,word,getrand(0,size));

    //     if(size % 10000 == 0){
    //         listnode *node;

    //         time_hashtab = wtime();
    //         for(int n = 0;n < size * 100;n++){
    //             node = hashtab_lookup(hashtab,word);
    //         }
    //         time_hashtab = wtime() - time_hashtab;

    //         printf("size - %d  time - %.6lf  colisias - %d\n",size,time_hashtab,colisias);
    //         colisias = 0;
    //     }
    // }
   
    // printf("\nELFHash\n");

    // for(int size = 1;size <= 200000;size++){
    //     char word[20];

    //     fgets(word,20,file);
    //     ELF_add(hashtab_ELF,word,getrand(0,size));

    //     if(size % 10000 == 0){
    //         listnode *node;

    //         time_hashtab = wtime();

    //         for(int n = 0;n < size * 100;n++){
    //             node = ELFHash_lookup(hashtab_ELF,word);
    //         }

    //         time_hashtab = wtime() - time_hashtab;

    //         printf("size - %d  time - %.6lf  colisias - %d\n",size,time_hashtab,colisias);
    //         colisias = 0;
    //     }
    // }

    /*test*/

    // bstree *test = NULL;

    // test = bstree_create(100,"root");
    // bstree_add(test,52,"one");
    // bstree_add(test,116,"two");
    // bstree_add(test,71,"three");
    // bstree_add(test,122,"four");
    // bstree_add(test,34,"five");
    // bstree_add(test,166,"six");
    // bstree_add(test,102,"seven");
    // bstree_add(test,90,"eight");
    // bstree_add(test,119,"nine");
    // bstree_add(test,99,"ten");
    // print_bstree(test,0);
    // bstree_delete(test,"four");
    // printf("Delete four\t========================\n\n");
    // print_bstree(test,0);
    // bstree_delete_all(test);
    return 0;
}