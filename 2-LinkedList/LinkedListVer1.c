#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    struct node *next;
    int data;
} Node;

typedef struct {
    Node *head;
    int count;
} List;

void initialize(List *L);
void makeEmpty(List *L);
void insertFirst(List *L, int data);
void insertLast(List *L, int data);
void insertPos(List *L, int data, int index);
void deleteStart(List *L);
void deleteLast(List *L);
void deletePos(List *L, int index);

int  retrieve(List *L, int index);
int  locate(List *L, int data);
void display(List *L);

int main(void) {
    List L;
    initialize(&L);

    insertFirst(&L, 1);
    insertLast(&L, 2);
    insertPos(&L, 3, 1);
    deletePos(&L, 1);

    int x = retrieve(&L, 1);
    if (x != -1)
        printf("Data in index 1 is %d\n", x);
    else
        printf("Nonexistent\n");

    locate(&L, 1) != -1 ? printf("Data 1 was found\n")
                        : printf("Data 1 was not found\n");
    locate(&L, 3) != -1 ? printf("Data 3 was found\n")
                        : printf("Data 3 was not found\n");

    display(&L);
    makeEmpty(&L);
    return 0;
}

void initialize(List *L) {
    L->head = NULL;
    L->count = 0;
}

void makeEmpty(List *L) {
    Node *trav = L->head;
    while (trav != NULL) {
        Node *next = trav->next;
        free(trav);
        trav = next;
    }
    L->head = NULL;
    L->count = 0;
}

void insertFirst(List *L, int data) {
    Node *newNode = calloc(1, sizeof(Node));
    newNode->data = data;
    newNode->next = L->head;
    L->head = newNode;
    L->count++;
}

void insertLast(List *L, int data) {
    if (L->count == 0) {
        insertFirst(L, data);
        return;
    }

    Node *newNode = calloc(1, sizeof(Node));
    newNode->data = data;

    Node *trav;
    for (trav = L->head; trav->next != NULL; trav = trav->next);
    trav->next = newNode;
    L->count++;
}

void insertPos(List *L, int data, int index) {
    if (index < 0 || index > L->count)
        return;
    if (index == 0) {
        insertFirst(L, data);
        return;
    }
    if (index == L->count) {
        insertLast(L, data);
        return;
    }

    Node *newNode = calloc(1, sizeof(Node));
    newNode->data = data;

    Node *trav = L->head;
    for (int i = 0; i < index - 1; i++)
        trav = trav->next;

    newNode->next = trav->next;
    trav->next = newNode;
    L->count++;
}

void deleteStart(List *L) {
    if (L->count == 0)
        return;

    Node *del = L->head;
    L->head = L->head->next;
    free(del);

    if (--L->count == 0)
        L->head = NULL;
}

void deleteLast(List *L) {
    if (L->count == 0)
        return;
    if (L->count == 1) {
        deleteStart(L);
        return;
    }

    Node *trav = L->head;
    for (int i = 0; i < L->count - 2; i++)
        trav = trav->next;

    Node *del = trav->next;
    trav->next = NULL;
    free(del);
    L->count--;
}

void deletePos(List *L, int index) {
    if (index < 0 || index >= L->count)
        return;
    if (index == 0) {
        deleteStart(L);
        return;
    }

    Node *trav = L->head;
    for (int i = 0; i < index - 1; i++)
        trav = trav->next;

    Node *del = trav->next;
    trav->next = del->next;
    free(del);
    L->count--;
}

int retrieve(List *L, int index) {
    if (index < 0 || index >= L->count)
        return -1;

    Node *trav = L->head;
    for (int i = 0; i < index; i++)
        trav = trav->next;
    return trav->data;
}

int locate(List *L, int data) {
    Node *trav = L->head;
    int index = 0;
    while (trav != NULL && trav->data != data) {
        trav = trav->next;
        index++;
    }
    return trav != NULL ? index : -1;
}

void display(List *L) {
    printf("Linked List: ");
    Node *trav = L->head;
    while (trav != NULL) {
        printf("%d -> ", trav->data);
        trav = trav->next;
    }
    printf("NULL\n");
}
