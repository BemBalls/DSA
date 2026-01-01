#include <stdio.h>
#include <stdbool.h>

#define SET_SIZE 8
typedef bool Set[SET_SIZE];

void set_init(Set s);
void set_add(Set s, int elem);
void set_remove(Set s, int elem);
bool set_contains(Set s, int elem);
void set_union(Set a, Set b, Set out);
void set_intersection(Set a, Set b, Set out);
void set_difference(Set a, Set b, Set out);
void set_print(Set s);

int main(void) {
    Set A, B, C;

    set_init(A);
    set_init(B);
    set_init(C);

    set_add(A, 0);
    set_add(A, 1);
    set_add(A, 2);
    set_add(A, 3);
    set_print(A);

    set_add(B, 7);
    set_add(B, 6);
    set_add(B, 5);
    set_print(B);

    bool found = set_contains(A, 1);
    printf(found ? "\nElement 1 in A is found\n" : "\nNah\n");

    found = set_contains(A, 7);
    printf(found ? "\nElement 7 in A is found\n" : "\nNah\n");

    set_union(A, B, C);
    printf("\nPrinting Union\n");
    set_print(C);

    set_add(B, 4);
    set_add(B, 3);
    set_intersection(A, B, C);
    printf("\nPrinting intersection\n");
    set_print(C);

    set_difference(A, B, C);
    printf("\nPrinting difference\n");
    set_print(C);

    return 0;
}

void set_init(Set s) {
    for (int i = 0; i < SET_SIZE; i++)
        s[i] = false;
}

void set_add(Set s, int elem) {
    if (elem >= 0 && elem < SET_SIZE) {
        s[SET_SIZE - 1 - elem] = true;
        printf("\nElement %d is now true\n", elem);
    } else {
        printf("\nInvalid element cannot insert\n");
    }
}

void set_remove(Set s, int elem) {
    if (elem >= 0 && elem < SET_SIZE) {
        s[SET_SIZE - 1 - elem] = false;
        printf("\nElement %d is now false\n", elem);
    } else {
        printf("\nInvalid element cannot delete\n");
    }
}

bool set_contains(Set s, int elem) {
    if (elem >= 0 && elem < SET_SIZE)
        return s[SET_SIZE - 1 - elem];
    return false;
}

void set_union(Set a, Set b, Set out) {
    for (int i = 0; i < SET_SIZE; i++)
        out[i] = (a[i] || b[i]);
}

void set_intersection(Set a, Set b, Set out) {
    for (int i = 0; i < SET_SIZE; i++)
        out[i] = (a[i] && b[i]);
}

void set_difference(Set a, Set b, Set out) {
    for (int i = 0; i < SET_SIZE; i++)
        out[i] = (a[i] && !b[i]);
}

void set_print(Set s) {
    printf("\nPrinting set\n");
    for (int i = SET_SIZE - 1; i >= 0; i--) {
        if (s[i])
            printf("%d", i);
    }
    printf("\n\n");
}
