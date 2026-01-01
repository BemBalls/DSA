#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *head;
    int count;
} List;

List *list_create(void);
void  list_clear(List *L);
void  list_insert_front(List *L, int data);
void  list_insert_back(List *L, int data);
void  list_insert_at(List *L, int data, int index);
void  list_delete_front(List *L);
void  list_delete_back(List *L);
void  list_delete_at(List *L, int index);
int   list_get(List *L, int index);
int   list_index_of(List *L, int data);
void  list_print(List *L);

int main(void) {
    List *L = list_create();

    list_insert_front(L, 1);
    list_insert_front(L, 2);
    list_insert_front(L, 3);
    list_print(L);

    list_insert_back(L, 4);
    list_insert_back(L, 5);
    list_insert_back(L, 6);
    list_print(L);

    list_insert_at(L, 7, 0);
    list_print(L);

    list_insert_at(L, 8, 7);
    list_insert_at(L, 9, 8);
    list_print(L);

    list_delete_front(L);
    list_print(L);

    list_delete_back(L);
    list_print(L);

    list_delete_at(L, 0);
    list_print(L);

    list_delete_at(L, 5);
    list_print(L);

    list_delete_at(L, 4);
    list_print(L);

    int num = list_get(L, 1);
    printf("\nNumber at index 1 is %d\n", num);
    num = list_get(L, 20);
    if (num == -1)
        printf("\nNOT REAL\n");

    int ind = list_index_of(L, 4);
    printf("Number 4 is at index %d", ind);
    ind = list_index_of(L, 20);
    if (ind == -1)
        printf("\nNOT REAL\n");

    list_clear(L);
    free(L);
    return 0;
}

List *list_create(void) {
    List *L = malloc(sizeof(List));
    if (L == NULL) {
        printf("\nALLOCATION UNSUCCESSFUL RETRY AGAIN\n");
        exit(1);
    }
    L->head = NULL;
    L->count = 0;
    return L;
}

void list_clear(List *L) {
    Node *temp = L->head;
    while (temp != NULL) {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
    L->head = NULL;
    L->count = 0;
}

void list_insert_front(List *L, int data) {
    Node *n = malloc(sizeof(Node));
    n->data = data;
    n->next = L->head;
    L->head = n;
    L->count++;
}

void list_insert_back(List *L, int data) {
    if (L->head == NULL) {
        list_insert_front(L, data);
        return;
    }
    Node *n = malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;

    Node *t = L->head;
    for (int i = 0; i < L->count - 1; i++)
        t = t->next;

    t->next = n;
    L->count++;
}

void list_insert_at(List *L, int data, int index) {
    if (index > L->count) {
        printf("\nINVALID POSITION\n");
        return;
    }
    if (index == 0) {
        list_insert_front(L, data);
    } else if (index == L->count) {
        list_insert_back(L, data);
    } else {
        Node *n = malloc(sizeof(Node));
        n->data = data;

        Node *t = L->head;
        for (int i = 0; i < index - 1; i++)
            t = t->next;

        n->next = t->next;
        t->next = n;
        L->count++;
    }
}

void list_delete_front(List *L) {
    if (L->head == NULL) {
        printf("\nNothing to delete from the list\n");
        return;
    }
    Node *t = L->head;
    L->head = t->next;
    free(t);
    L->count--;
    printf("\nSuccessfully deleted starting node\n");
}

void list_delete_back(List *L) {
    if (L->head == NULL) {
        printf("\nNothing to delete from the list\n");
        return;
    }
    if (L->count == 1) {
        list_delete_front(L);
        return;
    }

    Node *t = L->head;
    int i = 0;
    while (i < L->count - 2) {
        t = t->next;
        i++;
    }
    Node *del = t->next;
    t->next = NULL;
    free(del);
    L->count--;
    printf("\nSuccessfully deleted last node\n");
}

void list_delete_at(List *L, int index) {
    if (index >= L->count) {
        printf("\nInvalid Index\n");
        return;
    }
    if (index == 0) {
        list_delete_front(L);
    } else if (index == L->count - 1) {
        list_delete_back(L);
    } else {
        Node *t = L->head;
        int i = 0;
        while (i < index - 1) {
            t = t->next;
            i++;
        }
        Node *del = t->next;
        t->next = del->next;
        free(del);
        L->count--;
        printf("\nNode at position %d has been freed\n", index);
    }
}

int list_get(List *L, int index) {
    if (index >= L->count) {
        printf("\nInvalid Position\n");
        return -1;
    }
    Node *t = L->head;
    int i = 0;
    while (i != index) {
        t = t->next;
        i++;
    }
    return t->data;
}

int list_index_of(List *L, int data) {
    if (L->head == NULL) {
        printf("\nLIST IS EMPTY\n");
        return -1;
    }
    Node *t = L->head;
    int i = 0;
    while (i < L->count && t != NULL) {
        if (t->data == data) {
            printf("Position found, returning index %d", i);
            return i;
        }
        t = t->next;
        i++;
    }
    printf("\nData %d was NOT found within the list\n", data);
    return -1;
}

void list_print(List *L) {
    if (L->head == NULL) {
        printf("\nList is Empty\n");
        return;
    }
    printf("\nLINK LIST: ");
    Node *t = L->head;
    for (int i = 0; i < L->count; i++) {
        printf("%d ", t->data);
        t = t->next;
    }
    printf(" Count: %d\n", L->count);
}
