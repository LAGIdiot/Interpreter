#include <stdio.h>
#include <stdlib.h>

#include "memory_manager.h"

#include <token.h>
#include <ial.h>


typedef struct binaryTree
{
int data;
struct binaryTree * rChild;
struct binaryTree * lChild;
} node;

void createNode(node **, Token);
void deleteTree(node *);
void printPreorder(node *);
node* search(node **, Token);

void createNode(node ** tree, Token *tTokenPtr) //funkcia na vytvaranie stromu
{
    node *temp = NULL;
    if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->lChild = temp->rChild = NULL;
        temp->data = *tTokenPtr;
        *tree = temp;
        return;
    }

    if((*tTokenPtr)->data < (*tree)->data)
    {
        createNode(&(*tree)->lChild, *tTokenPtr);
    }
    else if((*tTokenPtr)->data > (*tree)->data)
    {
        createNode(&(*tree)->rChild, *tTokenPtr);
    }

}

void printPreorder(node * tree) //skusobna funkcia na vypis stromu Preorder
{
    if (tree)
    {
        printf("%d\n",tree->data);
        printPreorder(tree->lChild);
        printPreorder(tree->rChild);
    }

}

void deleteTree(node * tree) //funkcia na vymazanie stromu s uvolnenim pamati
{
    if (tree)
    {
        deleteTree(tree->lChild);
        deleteTree(tree->rChild);
        free(tree);
    }
}

node* search(node ** tree, Token *tTokenPtr) //funkcia na vyhladavanie tokenu v strome
{
    if(!(*tree))
    {
        return NULL;
    }

    if((*tTokenPtr)->data < (*tree)->data)
    {
        search(&((*tree)->lChild), *tTokenPtr);
    }
    else if((*tTokenPtr)->data > (*tree)->data)
    {
        search(&((*tree)->rChild), *tTokenPtr);
    }
    else if((*tTokenPtr)->data == (*tree)->data)
    {
        return *tree;
    }
}

void main()
{
    node *root;
    node *tmp;
    Token *tTokenPtr;
    root = NULL;
    
    printf("Pre Order Display\n");
    do 
    {
        createNode(&root, *tTokenPtr);  
    }while((*tTokenPtr)->data != (*tree)->data); 
    
    printPreorder(root);
    
    tmp = search(&root, *tTokenPtr);
    if (tmp)
    {
        printf("Searched node=%d\n", tmp->data);
    }
    else
    {
        fprintf(stderr, "Token Not found in tree\n");
    }
    deleteTree(root); //vymaze strom, uvolni pamat
}
