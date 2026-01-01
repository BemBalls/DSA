#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

typedef struct {
    int *elemPtr;
    int count;
    int max;
} List;

List  initialize(List L);
List  insertPos(List L, int data, int position);
List  deletePos(List L, int position);
int   locate(List L, int data);
List  insertSorted(List L, int data);
void  display(List L);
List  resize(List L);

int main(void) {
    List L;
    int choice, data, pos, idx;

    L = initialize(L);

    while (1) {
        printf("\n----- MENU -----\n");
        printf("1. Insert at position\n");
        printf("2. Delete at position\n");
        printf("3. Locate data\n");
        printf("4. Insert sorted\n");
        printf("5. Display\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
        case 1:
            printf("Enter data: ");
            scanf("%d", &data);
            printf("Enter position (1..%d): ", L.count + 1);
            scanf("%d", &pos);
            L = insertPos(L, data, pos);
            break;
        case 2:
            printf("Enter position (1..%d): ", L.count);
            scanf("%d", &pos);
            L = deletePos(L, pos);
            break;
        case 3:
            printf("Enter data to search: ");
            scanf("%d", &data);
            idx = locate(L, data);
            if (idx == -1)
                printf("Data not found.\n");
            else
                printf("Data found at position %d.\n", idx + 1);
            break;
        case 4:
            printf("Enter data to insert (sorted list assumed): ");
            scanf("%d", &data);
            L = insertSorted(L, data);
            break;
        case 5:
            display(L);
            break;
        case 6:
            free(L.elemPtr);
            return 0;
        default:
            printf("Invalid choice.\n");
        }
    }

    free(L.elemPtr);
    return 0;
}

List initialize(List L) {
    L.elemPtr = (int *)malloc(LENGTH * sizeof(int));
    L.count = 0;
    L.max = LENGTH;
    return L;
}

List resize(List L) {
    int newMax = L.max * 2;
    int *newPtr = (int *)realloc(L.elemPtr, newMax * sizeof(int));
    if (newPtr == NULL) {
        printf("Resize failed.\n");
        return L;
    }
    L.elemPtr = newPtr;
    L.max = newMax;
    return L;
}

List insertPos(List L, int data, int position) {
    int i;

    if (position < 1 || position > L.count + 1) {
        printf("Invalid position.\n");
        return L;
    }
    if (L.count == L.max) {
        L = resize(L);
    }

    for (i = L.count; i >= position; i--) {
        L.elemPtr[i] = L.elemPtr[i - 1];
    }

    L.elemPtr[position - 1] = data;
    L.count++;
    return L;
}

List deletePos(List L, int position) {
    int i;

    if (L.count == 0) {
        printf("List is empty.\n");
        return L;
    }
    if (position < 1 || position > L.count) {
        printf("Invalid position.\n");
        return L;
    }

    for (i = position - 1; i < L.count - 1; i++) {
        L.elemPtr[i] = L.elemPtr[i + 1];
    }

    L.count--;
    return L;
}

int locate(List L, int data) {
    int i;
    for (i = 0; i < L.count; i++) {
        if (L.elemPtr[i] == data)
            return i;
    }
    return -1;
}

List insertSorted(List L, int data) {
    int i, pos;

    if (L.count == L.max) {
        L = resize(L);
    }

    pos = 0;
    while (pos < L.count && L.elemPtr[pos] <= data) {
        pos++;
    }

    for (i = L.count; i > pos; i--) {
        L.elemPtr[i] = L.elemPtr[i - 1];
    }

    L.elemPtr[pos] = data;
    L.count++;
    return L;
}

void display(List L) {
    int i;

    if (L.count == 0) {
        printf("List is empty.\n");
        return;
    }

    printf("List elements: ");
    for (i = 0; i < L.count; i++) {
        printf("%d ", L.elemPtr[i]);
    }
    printf("\n");
}
