#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX 20
#define TABLE 10

typedef struct {
    char key[4];
    int next;
} Node;

typedef struct {
    Node heap[MAX];
    int avail;
} VHeap;

void init(VHeap *vh);
int alloc(VHeap *vh);
void freeNode(VHeap *vh, int idx);

int hashKey(const char *str);

bool search(VHeap *vh, const char *key);
void insertKey(VHeap *vh);
void removeKey(VHeap *vh);
void show(VHeap *vh);

int main() {
    VHeap vh;
    int choice;
    bool run = true;

    init(&vh);

    while (run) {
        printf("\n1. Insert\n2. Delete\n3. Display\n4. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insertKey(&vh); break;
            case 2: removeKey(&vh); break;
            case 3: show(&vh); break;
            case 4: run = false; break;
            default: printf("Invalid\n");
        }
    }

    return 0;
}

void init(VHeap *vh) {
    vh->avail = TABLE;
    for (int i = 0; i < MAX; i++) {
        vh->heap[i].key[0] = '\0';
        vh->heap[i].next = (i + 1 < MAX) ? i + 1 : -1;
    }
    for (int i = 0; i < TABLE; i++) {
        vh->heap[i].next = -1;
    }
}

int alloc(VHeap *vh) {
    int idx = vh->avail;
    if (idx != -1) {
        vh->avail = vh->heap[idx].next;
    }
    return idx;
}

void freeNode(VHeap *vh, int idx) {
    vh->heap[idx].next = vh->avail;
    vh->avail = idx;
}

int hashKey(const char *str) {
    unsigned int hash = 5381;
    int c;
    while ((c = (unsigned char)*str++)) {
        hash = (hash << 5) + hash + c;
    }
    return hash % TABLE;
}

bool search(VHeap *vh, const char *key) {
    int idx = hashKey(key);
    while (idx != -1) {
        if (strcmp(vh->heap[idx].key, key) == 0) return true;
        idx = vh->heap[idx].next;
    }
    return false;
}

void insertKey(VHeap *vh) {
    char key[4];
    scanf("%s", key);

    int h = hashKey(key);
    int *trav = &vh->heap[h].next;

    if (vh->heap[h].key[0] == '\0') {
        strcpy(vh->heap[h].key, key);
        return;
    }

    while (*trav != -1 && strcmp(vh->heap[*trav].key, key) < 0) {
        trav = &vh->heap[*trav].next;
    }

    if (*trav != -1 && strcmp(vh->heap[*trav].key, key) == 0) return;

    int idx = alloc(vh);
    if (idx == -1) return;

    strcpy(vh->heap[idx].key, key);
    vh->heap[idx].next = *trav;
    *trav = idx;
}

void removeKey(VHeap *vh) {
    char key[4];
    scanf("%s", key);

    int h = hashKey(key);
    int *trav = &vh->heap[h].next;

    if (strcmp(vh->heap[h].key, key) == 0) {
        if (vh->heap[h].next == -1) {
            vh->heap[h].key[0] = '\0';
        } else {
            int temp = vh->heap[h].next;
            vh->heap[h] = vh->heap[temp];
            freeNode(vh, temp);
        }
        return;
    }

    while (*trav != -1 && strcmp(vh->heap[*trav].key, key) != 0) {
        trav = &vh->heap[*trav].next;
    }

    if (*trav == -1) return;

    int del = *trav;
    *trav = vh->heap[del].next;
    freeNode(vh, del);
}

void show(VHeap *vh) {
    for (int i = 0; i < TABLE; i++) {
        int trav = i;
        printf("[%d] ", i);
        if (vh->heap[trav].key[0] == '\0') {
            printf("EMPTY\n");
        } else {
            while (trav != -1) {
                printf("%s -> ", vh->heap[trav].key);
                trav = vh->heap[trav].next;
            }
            printf("NULL\n");
        }
    }
}
