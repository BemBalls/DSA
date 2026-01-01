#include <stdio.h>
#include <stdbool.h>

typedef struct {
    unsigned char bits;
} Set;

void init(Set *s);
void add(Set *s, int elem);
void removeElem(Set *s, int elem);
bool contains(Set s, int elem);

Set setUnion(Set a, Set b);
Set setIntersection(Set a, Set b);
Set setDifference(Set a, Set b);

void printSet(Set s);

int main() {
    Set A, B;

    init(&A);
    init(&B);

    add(&A, 0);
    add(&A, 1);
    add(&A, 2);
    add(&A, 3);
    printSet(A);

    add(&B, 5);
    add(&B, 6);
    add(&B, 7);
    printSet(B);

    Set u = setUnion(A, B);
    printSet(u);

    add(&B, 3);
    Set i = setIntersection(A, B);
    printSet(i);

    Set d = setDifference(A, B);
    printSet(d);

    if (contains(A, 1)) {
        printf("1 is found\n");
    }

    if (contains(A, 6)) {
        printf("6 is found\n");
    } else {
        printf("6 not found :(\n");
    }

    return 0;
}

void init(Set *s) {
    s->bits = 0;
}

void add(Set *s, int elem) {
    if (elem >= 0 && elem < 8) {
        s->bits |= (1 << elem);
    }
}

void removeElem(Set *s, int elem) {
    if (elem >= 0 && elem < 8) {
        s->bits &= ~(1 << elem);
    }
}

bool contains(Set s, int elem) {
    if (elem < 0 || elem >= 8) return false;
    return (s.bits & (1 << elem)) != 0;
}

Set setUnion(Set a, Set b) {
    Set r;
    r.bits = a.bits | b.bits;
    return r;
}

Set setIntersection(Set a, Set b) {
    Set r;
    r.bits = a.bits & b.bits;
    return r;
}

Set setDifference(Set a, Set b) {
    Set r;
    r.bits = a.bits & ~b.bits;
    return r;
}

void printSet(Set s) {
    printf("Set: ");
    for (int i = 0; i < 8; i++) {
        if ((s.bits >> i) & 1) {
            printf("%d ", i);
        }
    }
    printf("\n");
}
