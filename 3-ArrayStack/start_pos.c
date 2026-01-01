#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_MAX 10

typedef struct {
    int data[STACK_MAX];
    int top;
} Stack;

Stack *stack_create(void);
void   stack_destroy(Stack *s);
bool   stack_is_full(Stack *s);
bool   stack_is_empty(Stack *s);
void   stack_push(Stack *s, int value);
int    stack_pop(Stack *s);
int    stack_peek(Stack *s);
void   stack_print(Stack *s);

int main(void) {
    Stack *s = stack_create();

    stack_push(s, 1);
    stack_push(s, 2);
    stack_push(s, 3);
    stack_push(s, 4);

    stack_print(s);

    int x = stack_pop(s);
    printf("\nPopped: %d\n", x);
    x = stack_pop(s);
    printf("Popped: %d\n", x);

    stack_print(s);

    stack_destroy(s);
    return 0;
}

Stack *stack_create(void) {
    Stack *s = malloc(sizeof(Stack));
    if (s == NULL) {
        printf("Allocation failed\n");
        exit(1);
    }
    s->top = -1;
    return s;
}

void stack_destroy(Stack *s) {
    free(s);
}

bool stack_is_full(Stack *s) {
    return s->top == STACK_MAX - 1;
}

bool stack_is_empty(Stack *s) {
    return s->top == -1;
}

void stack_push(Stack *s, int value) {
    if (stack_is_full(s)) {
        printf("Stack overflow\n");
        return;
    }
    s->data[++s->top] = value;
}

int stack_pop(Stack *s) {
    if (stack_is_empty(s)) {
        printf("Stack underflow\n");
        return -1;
    }
    return s->data[s->top--];
}

int stack_peek(Stack *s) {
    if (stack_is_empty(s))
        return -1;
    return s->data[s->top];
}

void stack_print(Stack *s) {
    if (stack_is_empty(s)) {
        printf("\nStack is empty\n");
        return;
    }
    printf("\nStack\n");
    for (int i = 0; i <= s->top; i++)
        printf("Index %d: %d\n", i, s->data[i]);
}
