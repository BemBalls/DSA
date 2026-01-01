#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

typedef struct {
    int *elemPtr;
    int count;
    int max;
} List;

void initialize(List *L);
void insertPos(List *L, int data, int position);
void deletePos(List *L, int position);
int  locate(List *L, int data);
int  retrieve(List *L, int position);
void insertSorted(List *L, int data);
void display(List *L);
void resize(List *L);
void makeNULL(List *L);

int main(void) {
    List L;
    int choice, data, pos, idx;

    initialize(&L);

    while (1) {
        printf("\n----- MENU -----\n");
        printf("1. Insert at position\n");
        printf("2. Delete at position\n");
        printf("3. Locate data\n");
        printf("4. Retrieve at position\n");
        printf("5. Insert sorted\n");
        printf("6. Display\n");
        printf("7. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
        case 1:
            printf("Enter data: ");
            scanf("%d", &data);
            printf("Enter position (1..%d): ", L.count + 1);
            scanf("%d", &pos);
            insertPos(&L, data, pos);
            break;
        case 2:
            printf("Enter position (1..%d): ", L.count);
            scanf("%d", &pos);
            deletePos(&L, pos);
            break;
        case 3:
            printf("Enter data to search: ");
            scanf("%d", &data);
            idx = locate(&L, data);
            if (idx == -1)
                printf("Data not found.\n");
            else
                printf("Data found at position %d.\n", idx + 1);
            break;
        case 4:
            printf("Enter position (1..%d): ", L.count);
            scanf("%d", &pos);
            data = retrieve(&L, pos);
            if (data != -1)
                printf("Element at position %d is %d.\n", pos, data);
            break;
        case 5:
            printf("Enter data to insert (sorted list assumed): ");
            scanf("%d", &data);
            insertSorted(&L, data);
            break;
        case 6:
            display(&L);
            break;
        case 7:
            makeNULL(&L);
            return 0;
        default:
            printf("Invalid choice.\n");
        }
    }

    makeNULL(&L);
    return 0;
}

void initialize(List *L) {
    L->elemPtr = (int *)malloc(LENGTH * sizeof(int));
    L->count = 0;
    L->max = LENGTH;
}

void resize(List *L) {
    int newMax = L->max * 2;
    int *newPtr = (int *)realloc(L->elemPtr, newMax * sizeof(int));
    if (newPtr == NULL) {
        printf("Resize failed.\n");
        return;
    }
    L->elemPtr = newPtr;
    L->max = newMax;
}

void insertPos(List *L, int data, int position) {
    int i;

    if (position < 1 || position > L->count + 1) {
        printf("Invalid position.\n");
        return;
    }
    if (L->count == L->max) {
        resize(L);
    }

    for (i = L->count; i >= position; i--) {
        L->elemPtr[i] = L->elemPtr[i - 1];
    }

    L->elemPtr[position - 1] = data;
    L->count++;
}

void deletePos(List *L, int position) {
    int i;

    if (L->count == 0) {
        printf("List is empty.\n");
        return;
    }
    if (position < 1 || position > L->count) {
        printf("Invalid position.\n");
        return;
    }

    for (i = position - 1; i < L->count - 1; i++) {
        L->elemPtr[i] = L->elemPtr[i + 1];
    }

    L->count--;
}

int locate(List *L, int data) {
    int i;
    for (i = 0; i < L->count; i++) {
        if (L->elemPtr[i] == data)
            return i;
    }
    return -1;
}

int retrieve(List *L, int position) {
    if (position < 1 || position > L->count) {
        printf("Invalid position.\n");
        return -1;
    }
    return L->elemPtr[position - 1];
}

void insertSorted(List *L, int data) {
    int i, pos;

    if (L->count == L->max) {
        resize(L);
    }

    pos = 0;
    while (pos < L->count && L->elemPtr[pos] <= data) {
        pos++;
    }

    for (i = L->count; i > pos; i--) {
        L->elemPtr[i] = L->elemPtr[i - 1];
    }

    L->elemPtr[pos] = data;
    L->count++;
}

void display(List *L) {
    int i;

    if (L->count == 0) {
        printf("List is empty.\n");
        return;
    }

    printf("List elements: ");
    for (i = 0; i < L->count; i++) {
        printf("%d ", L->elemPtr[i]);
    }
    printf("\n");
}

void makeNULL(List *L) {
    free(L->elemPtr);
    L->elemPtr = NULL;
    L->count = 0;
    L->max = 0;
}
