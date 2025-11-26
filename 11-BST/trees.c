#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int data;
    struct node *left;
    struct node *right;
}Node, *BST;

void insert(BST * T, int value);
void delete(BST * T, int value);
void preorder(BST T);
void postorder(BST T);
void inorder(BST T);

int main(){
    BST T = NULL;
    insert(&T, 3);
    insert(&T, 5);
    insert(&T, 9);
    insert(&T, 1);
    insert(&T, 8);
    insert(&T, 4);
    insert(&T, 2);
    insert(&T, 6);
    insert(&T, 7);

    printf("Inorder: ");
    inorder(T);
    printf("\nPreorder: ");
    preorder(T);
    printf("\nPostorder: ");
    postorder(T);
    printf("\n");


    delete(&T, 5);
    printf("\n\nInorder: ");
    inorder(T);
    printf("\nPreorder: ");
    preorder(T);
    printf("\nPostorder: ");
    postorder(T);
}


void insert(BST * T, int value){
    BST * trav = T;

    while(*trav != NULL){
        printf("Im traversing\n");
        if((*trav) -> data == value){
            printf("Duplication of data, terminating\n");
            return;
        }
        trav = (*trav)->data > value ? &(*trav)->left : &(*trav)->right;
    }
    if (*trav == NULL){
        *trav = calloc(1, sizeof(Node));
        (*trav)->data = value;
        printf("Value %d has been inserted\n", (*trav)->data);
    }
}

void delete(BST *T, int value){
    BST * trav = T;
    
    while(*trav != NULL){
        printf("im traversing wooo..\n");

        if((*trav)->data == value){
            break;
        }

        if((*trav)->data > value){
            trav = &(*trav)->left;
        }else{
            trav = &(*trav)->right;
        }
    }
    if(*trav == NULL){
        printf("Value was not found\n");
        return;
    }

    printf("Value %d was found, Deleting IT!\n", (*trav)->data);

    if((*trav)->left == NULL && (*trav)->right == NULL){
        free(*trav);
        *trav = NULL;
        printf("Node with no children removed!\n");
    }
    else if((*trav)->left != NULL && (*trav)->right == NULL){
        BST temp = (*trav)->left;
        free(*trav);
        *trav = temp;
        printf("Node with left child removed and replaced!\n");
    }
    else if((*trav)->left == NULL && (*trav)->right != NULL){
        BST temp = (*trav)->right;
        free(*trav);
        printf("trav data is %d\n", (*trav)->data);
        printf("temp data is %d\n", temp->data);
        *trav = temp;
        printf("Node with right child only removed and replaced!\n");
    }else{
        BST left = (*trav)->right;
        while(left->left !=NULL){
            printf("traversing for replacement eru ugh.. \n");
            left = left->left;
        }
        (*trav)->data = left->data;
        delete(&(*trav)->right, left->data);

    }
    printf("I did delete data\n");
}

void preorder(BST T){
    if(T != NULL){
        printf("%d ", T->data);
        preorder(T->left);
        preorder(T->right);
    }
}

void postorder(BST T){
    if(T != NULL){
        preorder(T->left);
        preorder(T->right);
        printf("%d ", T->data);
    }
}

void inorder(BST T){
    if(T != NULL){
        preorder(T->left);
        printf("%d ", T->data);
        preorder(T->right);
    }
}