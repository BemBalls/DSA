#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int elem;
    int next;
} Cell;

typedef struct {
    Cell data[MAX];
    int avail;
} VHeap;

void initHeap(VHeap *vh);
int allocate(VHeap *vh);
void freeSpace(VHeap *vh, int idx);

void insertFront(int *list, VHeap *vh, int value);
void insertBack(int *list, VHeap *vh, int value);
void insertAt(int *list, VHeap *vh, int value, int pos);
void insertOrdered(int *list, VHeap *vh, int value);

void removeOne(int *list, VHeap *vh, int value);
void removeAll(int *list, VHeap *vh, int value);

void printList(int list, VHeap vh);

int main() {
    VHeap vh;
    int list = -1;

    initHeap(&vh);

    insertFront(&list, &vh, 6);
    insertFront(&list, &vh, 7);
    insertBack(&list, &vh, 10);
    insertBack(&list, &vh, 10);
    insertAt(&list, &vh, 4, 2);
    insertOrdered(&list, &vh, 8);

    printList(list, vh);

    removeAll(&list, &vh, 10);
    printList(list, vh);

    return 0;
}

void initHeap(VHeap *vh) {
    vh->avail = MAX - 1;
    for (int i = MAX - 1; i > 0; i--) {
        vh->data[i].next = i - 1;
    }
    vh->data[0].next = -1;
}

int allocate(VHeap *vh) {
    int idx = vh->avail;
    if (idx != -1) {
        vh->avail = vh->data[idx].next;
    }
    return idx;
}

void freeSpace(VHeap *vh, int idx) {
    vh->data[idx].next = vh->avail;
    vh->avail = idx;
}

void insertFront(int *list, VHeap *vh, int value) {
    int idx = allocate(vh);
    if (idx == -1) return;

    vh->data[idx].elem = value;
    vh->data[idx].next = *list;
    *list = idx;
}

void insertBack(int *list, VHeap *vh, int value) {
    int idx = allocate(vh);
    if (idx == -1) return;

    vh->data[idx].elem = value;
    vh->data[idx].next = -1;

    int *trav = list;
    while (*trav != -1) {
        trav = &vh->data[*trav].next;
    }
    *trav = idx;
}

void insertAt(int *list, VHeap *vh, int value, int pos) {
    int idx = allocate(vh);
    if (idx == -1) return;

    int *trav = list;
    for (int i = 0; i < pos && *trav != -1; i++) {
        trav = &vh->data[*trav].next;
    }

    vh->data[idx].elem = value;
    vh->data[idx].next = *trav;
    *trav = idx;
}

void insertOrdered(int *list, VHeap *vh, int value) {
    int idx = allocate(vh);
    if (idx == -1) return;

    int *trav = list;
    while (*trav != -1 && vh->data[*trav].elem < value) {
        trav = &vh->data[*trav].next;
    }

    vh->data[idx].elem = value;
    vh->data[idx].next = *trav;
    *trav = idx;
}

void removeOne(int *list, VHeap *vh, int value) {
    int *trav = list;
    while (*trav != -1 && vh->data[*trav].elem != value) {
        trav = &vh->data[*trav].next;
    }

    if (*trav == -1) return;

    int del = *trav;
    *trav = vh->data[del].next;
    freeSpace(vh, del);
}

void removeAll(int *list, VHeap *vh, int value) {
    int *trav = list;
    while (*trav != -1) {
        if (vh->data[*trav].elem == value) {
            int del = *trav;
            *trav = vh->data[del].next;
            freeSpace(vh, del);
        } else {
            trav = &vh->data[*trav].next;
        }
    }
}

void printList(int list, VHeap vh) {
    printf("Cursor List: ");
    for (int i = list; i != -1; i = vh.data[i].next) {
        printf("%d -> ", vh.data[i].elem);
    }
    printf("NULL\n\n");
}
