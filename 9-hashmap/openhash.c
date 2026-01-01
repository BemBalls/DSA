#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

typedef struct node {
    int elem;
    struct node *next;
} Node, *Bucket;

void table_init(Bucket table[]);
void table_print(Bucket table[]);
void table_insert(Bucket table[], int key);
void table_remove(Bucket table[], int key);
void table_clear(Bucket table[]);
int  hash_func(int key);

int main(void) {
    Bucket table[TABLE_SIZE];

    table_init(table);

    table_insert(table, 10);
    table_insert(table, 383);
    table_insert(table, 32);
    table_insert(table, 932);
    table_insert(table, 83872);
    table_insert(table, 872);
    table_insert(table, 312893);
    table_insert(table, 67243);

    table_print(table);

    table_remove(table, 32);
    table_remove(table, 872);
    table_print(table);

    table_clear(table);
    table_print(table);

    return 0;
}

void table_init(Bucket table[]) {
    for (int i = 0; i < TABLE_SIZE; i++)
        table[i] = NULL;
}

void table_print(Bucket table[]) {
    printf("OPEN HASH\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %d: ", i);
        Node *trav = table[i];
        while (trav != NULL) {
            printf("%d -> ", trav->elem);
            trav = trav->next;
        }
        printf("NULL\n");
    }
    printf("\n\n");
}

void table_insert(Bucket table[], int key) {
    int idx = hash_func(key);

    Node *n = calloc(1, sizeof(Node));
    n->elem = key;
    n->next = table[idx];
    table[idx] = n;
}

void table_remove(Bucket table[], int key) {
    int idx = hash_func(key);

    Node **trav = &table[idx];
    while (*trav != NULL && (*trav)->elem != key)
        trav = &(*trav)->next;

    if (*trav == NULL) return;

    Node *del = *trav;
    *trav = (*trav)->next;
    free(del);
}

int hash_func(int key) {
    return ((key + 132 - 10) * 5) % TABLE_SIZE;
}

void table_clear(Bucket table[]) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        while (table[i] != NULL) {
            Node *del = table[i];
            table[i] = table[i]->next;
            free(del);
        }
    }
    printf("Cleaned!\n\n");
}
