#include <stdio.h>
#include <stdlib.h>

#include "memory_manager.h"

#include "token.h"
#include "ial.h"

void createNode(node *, Token);
void deleteTree(node);
void printPreorder(node);
node* search(node *, Token);

/*funkcia na vytvaranie node*/
void createNode(node * tree, Token *tTokenPtr) 
{
    node temp = NULL;
    if(!(*tree))
    {
        temp = (node)malloc(sizeof(node));
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
/*skusobna funkcia na vypis stromu Preorder
void printPreorder(node tree) 
{
    if (tree)
    {
        printf("%d\n",tree->data);
        printPreorder(tree->lChild);
        printPreorder(tree->rChild);
    }

}*/
/*funkcia na vymazanie stromu s uvolnenim pamati*/
void deleteTree(node tree) 
{
    if (tree)
    {
        deleteTree(tree->lChild);
        deleteTree(tree->rChild);
        free(tree);
    }
}
/*funkcia na vyhladavanie tokenu v strome*/
node* search(node * tree, Token *tTokenPtr) 
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
/*funkcia ktora vola ostatne funkcie, vytvara strom a hlada v nom token*/
void treeCreation()
{
    node root;
    node tmp;
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
