#include <stdio.h>
#include <stdbool.h>

typedef unsigned char BitSet;

void set_init(BitSet *s);
void set_insert(BitSet *s, int elem);
void set_delete(BitSet *s, int elem);
bool set_contains(BitSet *s, int elem);
BitSet set_union(BitSet a, BitSet b);
BitSet set_intersection(BitSet a, BitSet b);
BitSet set_difference(BitSet a, BitSet b);
void set_print(BitSet s);

int main(void) {
    BitSet A, B;

    set_init(&A);
    set_init(&B);

    set_insert(&A, 0);
    set_insert(&A, 1);
    set_insert(&A, 2);
    set_insert(&A, 3);
    printf("\nDisplaying Set A\n");
    set_print(A);

    printf("\nINSERTION\n");
    set_insert(&B, 3);
    set_insert(&B, 4);
    set_insert(&B, 6);
    set_insert(&B, 7);
    set_insert(&B, 9);
    set_insert(&B, -1);
    printf("\nDisplaying Set B\n");
    set_print(B);

    printf("\nDELETION\n");
    set_delete(&A, 1);
    printf("\nDisplaying Set A\n");
    set_print(A);
    set_delete(&B, 7);
    printf("\nDisplaying Set B\n");
    set_print(B);

    printf("\nis 3 valid: %d\n", set_contains(&B, 3));

    BitSet uni = set_union(A, B);
    printf("\nDisplaying Union\n");
    set_print(uni);

    BitSet inter = set_intersection(A, B);
    printf("\nDisplaying Intersection\n");
    set_print(inter);

    BitSet diff = set_difference(A, B);
    printf("\nDisplaying Difference\n");
    set_print(diff);

    return 0;
}

void set_init(BitSet *s) {
    *s = 0;
}

void set_insert(BitSet *s, int elem) {
    if (elem >= 0 && elem < 8) {
        BitSet mask = (BitSet)1 << elem;
        *s |= mask;
    } else {
        printf("\nCannot insert, element is invalid\n");
    }
}

void set_delete(BitSet *s, int elem) {
    if (elem >= 0 && elem < 8) {
        BitSet mask = (BitSet)1 << elem;
        *s &= ~mask;
    } else {
        printf("\nCannot delete, element is invalid.\n");
    }
}

bool set_contains(BitSet *s, int elem) {
    if (elem < 0 || elem >= 8) return false;
    BitSet mask = (BitSet)1 << elem;
    return (*s & mask) != 0;
}

BitSet set_union(BitSet a, BitSet b) {
    return (BitSet)(a | b);
}

BitSet set_intersection(BitSet a, BitSet b) {
    return (BitSet)(a & b);
}

BitSet set_difference(BitSet a, BitSet b) {
    return (BitSet)(a & (BitSet)~b);
}

void set_print(BitSet s) {
    for (int i = 0; i < 8; i++) {
        if ((s >> i) & 1)
            printf("%d ", i);
    }
    printf("\n");
}
