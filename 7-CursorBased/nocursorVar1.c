#include <stdio.h>
#include <stdlib.h>

#define MAX 5

typedef struct {
    int elem;
    int next;
} Cell, HeapSpace[MAX];

typedef struct {
    HeapSpace H;
    int avail;
} VHeap;

typedef int CursorList;

void vheap_init(VHeap *vh);
int  vheap_alloc(VHeap *vh);
void vheap_free(VHeap *vh, int index);

void clist_insert_front(CursorList *L, VHeap *vh, int elem);
void clist_insert_back(CursorList *L, VHeap *vh, int elem);
void clist_insert_at(CursorList *L, VHeap *vh, int elem, int pos);
void clist_insert_sorted(CursorList *L, VHeap *vh, int elem);
void clist_delete_first(CursorList *L, VHeap *vh, int elem);
void clist_delete_all(CursorList *L, VHeap *vh, int elem);
void clist_print(CursorList L, VHeap vh);

int main(void) {
    VHeap vh;
    CursorList L = -1;

    vheap_init(&vh);

    clist_insert_front(&L, &vh, 1);
    clist_insert_front(&L, &vh, 1);
    clist_insert_back(&L, &vh, 2);
    clist_insert_at(&L, &vh, 4, 0);
    clist_insert_sorted(&L, &vh, 3);

    clist_print(L, vh);

    clist_delete_all(&L, &vh, 1);
    clist_print(L, vh);

    return 0;
}

void vheap_init(VHeap *vh) {
    vh->avail = 0;
    for (int i = 0; i < MAX - 1; i++)
        vh->H[i].next = i + 1;
    vh->H[MAX - 1].next = -1;
}

int vheap_alloc(VHeap *vh) {
    if (vh->avail == -1)
        return -1;
    int idx = vh->avail;
    vh->avail = vh->H[idx].next;
    return idx;
}

void vheap_free(VHeap *vh, int index) {
    vh->H[index].next = vh->avail;
    vh->avail = index;
}

void clist_insert_front(CursorList *L, VHeap *vh, int elem) {
    int idx = vheap_alloc(vh);
    if (idx == -1) return;

    vh->H[idx].elem = elem;
    vh->H[idx].next = *L;
    *L = idx;
}

void clist_insert_back(CursorList *L, VHeap *vh, int elem) {
    int idx = vheap_alloc(vh);
    if (idx == -1) return;

    vh->H[idx].elem = elem;
    vh->H[idx].next = -1;

    int *trav = L;
    while (*trav != -1)
        trav = &vh->H[*trav].next;

    *trav = idx;
}

void clist_insert_at(CursorList *L, VHeap *vh, int elem, int pos) {
    int idx = vheap_alloc(vh);
    if (idx == -1) return;

    vh->H[idx].elem = elem;

    int *trav = L;
    for (int i = 0; i < pos && *trav != -1; i++)
        trav = &vh->H[*trav].next;

    vh->H[idx].next = *trav;
    *trav = idx;
}

void clist_insert_sorted(CursorList *L, VHeap *vh, int elem) {
    int idx = vheap_alloc(vh);
    if (idx == -1) return;

    vh->H[idx].elem = elem;

    int *trav = L;
    while (*trav != -1 && elem >= vh->H[*trav].elem)
        trav = &vh->H[*trav].next;

    vh->H[idx].next = *trav;
    *trav = idx;
}

void clist_delete_first(CursorList *L, VHeap *vh, int elem) {
    int *trav = L;
    while (*trav != -1 && vh->H[*trav].elem != elem)
        trav = &vh->H[*trav].next;

    if (*trav == -1) return;

    int del = *trav;
    *trav = vh->H[del].next;
    vheap_free(vh, del);
}

void clist_delete_all(CursorList *L, VHeap *vh, int elem) {
    int *trav = L;
    while (*trav != -1) {
        if (vh->H[*trav].elem == elem) {
            int del = *trav;
            *trav = vh->H[del].next;
            vheap_free(vh, del);
        } else {
            trav = &vh->H[*trav].next;
        }
    }
}

void clist_print(CursorList L, VHeap vh) {
    printf("Cursor List: ");
    for (int t = L; t != -1; t = vh.H[t].next)
        printf("%d -> ", vh.H[t].elem);
    printf("NULL\n\n");
}
