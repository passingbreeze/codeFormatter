// #ifndef __LIST_H__
// #define __LIST_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define nullptr ((void*)0)

enum {INSERT = 1, FIND, DEL, PRINT, STOP, QUIT};

typedef struct list {
    int data;
    struct list *prev;
    struct list *next;
    bool ishead, istail;
} list;

bool isempty(list**);
list* pos(list**, int);
void insert(list**, int, int);
list* find(list**, int);
void erase(list**, int);
void showlist(list**);
void clear(list**);
int size(list**);
int at(list**, int);

// #endif

int main(int argc, char *argv[]) {
    list *root = nullptr;

    int select=0, kth=0, value=0;
    while(true) {
        printf("\nLet's make List!\n");
        printf("1. INSERT | 2. FIND SOMETHING | 3. DELETE SOMETHING | 4. SHOW LIST | 5. STOP MANIPULATE LIST | 6. QUIT PROGRAM\n >> ");
        scanf("%d", &select);
        if(select == STOP)
            break;
        if(select == QUIT) {
            printf("\nProgram will be terminated...\n");
            clear(&root);
            exit(EXIT_SUCCESS);
        }
        switch(select) {
        case INSERT:
            printf("Enter \'k\'th pos and input data >>  ");
            scanf("%d%d", &kth, &value);
            if(root == nullptr)
                printf("list begin!\n");
            insert(&root, kth, value);
            printf("%d elements in list\n", size(&root));
            break;
        case FIND:
            printf("what number do you wanna find? >> ");
            scanf("%d", &value);
            if(find(&root, value) != nullptr)
                printf("%d is in list!\n", find(&root,value)->data);
            else
                printf("Not found...\n");
            break;
        case DEL:
            printf("what number do you wanna delete? >> ");
            scanf("%d", &value);
            erase(&root, value);
            break;
        case PRINT:
            if(!size(&root))
                printf("No Elements in list!\n");
            else {
                printf("%d elements are in list.\n In list : ", size(&root));
                showlist(&root);
                printf("\n");
            }
            break;
        default:
            printf("\nPlease input the number between 1 and 6\n");
            break;
        }
    }
    clear(&root);
    return EXIT_SUCCESS;
}

int size(list** root) {
    int count=1;
    list *temp = (*root);
    if(temp == nullptr)
        return 0;
    else if(temp->next == (*root))
        return 1;
    else {
        while(!temp->next->istail) {
            temp = temp->next;
            count++;
        }
    }
    return count;
}

bool isempty(list **root) {
    return size(root)==0;
}

void clear(list **root) {
    list *temp = nullptr;
    while(!(*root)->istail) {
        temp = (*root);
        (*root) = (*root)->next;
        free(temp);
    }
    free(*root);
}

list* pos(list** root, int i) {
    int count=0;
    list *temp = (*root);
    if(isempty(&temp) || i > size(&temp)) {
        fputs("out of range", stderr);
        exit(EXIT_FAILURE);
    } else if(i==0) {
        while(!temp->ishead)
            temp = temp->next;
    } else if(i>0) {
        while(count < i) {
            temp = temp->next;
            count++;
        }
    } else {
        while(count < -i) {
            temp = temp->prev;
            count++;
        }
    }
    return temp;
}

int at(list** root, int i) {
    return pos(root, i)->data;
}

list* find(list **root, int v) {
    if(isempty(root)) {
        return nullptr;
    } else {
        list *temp = (*root);
        while(temp->data != v)
            temp = temp->next;

        return temp;
    }
}

void insert(list **root, int kth, int v) {
    list* new = (list*)malloc(sizeof(list));
    list* temp = *root;

    new->data = v;
    new->prev = new->next = nullptr;
    new->ishead = false;
    new->istail = true;

    if(isempty(root)) {
        *root = new;
        (*root)->ishead = true;
        (*root)->istail = true;
        (*root)->prev = (*root)->next = *root;
    } else {
        if(kth < size(root)) {
            temp = pos(root, kth);
            new->istail = false;
            temp->next = new;
            new->prev = temp;
            new->next = temp->next;
            temp->next->prev = new;
        } else { // need to modify
            while(!temp->istail) {
                printf("node data : %d\n", temp->data);
                temp = temp->next;
            }
            printf("\nlist size = %d, tail? == %d\n", size(root), temp->istail);
            temp->istail = false;
            temp->next = new;
            new->prev = temp;
            new->next = (*root);
            (*root)->prev = new;
        }
    }
}

void erase(list **root, int v) {
    if(isempty(root)) {
        printf("list is empty.");
        return;
    } else {
        list *temp = find(root,v);
        temp->next->prev = temp->prev;
        temp->prev->next = temp->next;
        free(temp);
    }
}

void showlist(list** root) {
    list *temp = *root;
    while(temp != nullptr) {
        printf("%d -> ", temp->data);
        temp = temp->next;
        if(temp->istail)
            break;
    }
    printf("end\n");
}