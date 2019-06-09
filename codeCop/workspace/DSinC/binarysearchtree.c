// you can make header files from this line

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

enum {INSERT = 1, FIND, DEL, PRINT, STOP, BLANK=5};

typedef struct intbtree {
    int data;
    struct intbtree *left;
    struct intbtree *right;
} intbtree;

void insert(intbtree**, int);
void search(intbtree**, int);
void delete(intbtree**);
void delNode(intbtree**, int);
void printTree(intbtree**, int);
void deallocTree(intbtree**);

// to this line.

int main() {
    intbtree *root = NULL;
    int value = 0, select = 0;

    while (true) {
        printf("\nLet's Make Binary Search Tree.\n");
        printf("1. INSERT | 2. FIND SOMETHING | 3. DELETE SOMETHING | 4. PRINT Tree! | 5. STOP... \n >> ");
        scanf("%d", &select);
        if (select == STOP) {
            deallocTree(&root);
            break;
        }
        switch (select) {
        case INSERT :
            printf("Enter new value you wanna input in tree. >> ");
            scanf("%d", &value);
            insert(&root, value);
            break;
        case FIND :
            printf("What value do you wanna find? >> ");
            scanf("%d", &value);
            search(&root, value);
            break;
        case DEL :
            printf("What value do you wanna erase? >> ");
            scanf("%d", &value);
            delNode(&root, value);
            break;
        case PRINT :
            printTree(&root, 0);
            break;
        default:
            printf("You should enter the number between 1 and 5.\n");
            break;
        }
    }
    return EXIT_SUCCESS;
}

void insert(intbtree** root, int v) {
    if ((*root) == NULL) {
        *root = (intbtree*)malloc(sizeof(intbtree));
        (*root)->left = NULL;
        (*root)->right = NULL;
        (*root)->data = v;
    } else {
        if (v > (*root)->data)
            insert(&((*root)->right), v);
        else
            insert(&((*root)->left), v);
    }
}

void search(intbtree** root, int v) {
    if ((*root)->data == v) {
        printf("\nTree has %d!\n", v);
        return;
    }
    if ((*root)->data != v) {
        printf("\nNot Found!\n");
        return;
    }
    if ((*root)->left!=NULL)
        search(&(*root)->left, v);
    if ((*root)->right!=NULL)
        search(&(*root)->right, v);
}


void delete(intbtree** root) {
    if((*root)->left == NULL && (*root)->right == NULL)
        *root = NULL;
    else {
        intbtree** temp = NULL;
        while((*root)->left != NULL) {
            temp = &((*root)->left);
            (*root)=(*root)->left;
        }
        delete(temp);
    }
}

void delNode(intbtree** root, int value) {
    if((*root)!=NULL) {
        if((*root)->data == value)
            delete(root);
        else if((*root)->data < value)
            delNode(&((*root)->right), value);
        else if((*root)->data > value)
            delNode(&((*root)->left), value);
    }
}

void printTree(intbtree **root, int space) {
    if((*root) == NULL)
        return;

    space += BLANK;

    printTree(&((*root)->right), space);
    printf("\n");
    for(int i = BLANK; i < space; ++i)
        printf(" ");
    printf("%d\n", (*root)->data);

    printTree(&((*root)->left), space);
}

void deallocTree(intbtree** root) {
    if((*root)!=NULL) {
        if((*root)->right==NULL && (*root)->left==NULL) {
            printf("freedom!\n");
            free((*root));
        }
        if((*root)->right!=NULL)
            deallocTree(&((*root)->right));

        if((*root)->left!=NULL)
            deallocTree(&((*root)->left));
    }
}
