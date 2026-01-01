#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_MAX 10

typedef struct {
    int data[STACK_MAX];
    int top;
} Stack;

Stack *stack_create(void);
bool   stack_is_full(Stack *s);
bool   stack_is_empty(Stack *s);
void   stack_push(Stack *s, int value);
int    stack_pop(Stack *s);
int    stack_peek(Stack *s);
void   stack_print(Stack *s);

int main(void) {
    Stack *s = stack_create();

    stack_push(s, 1);
    printf("\n%d data\n", s->data[s->top]);
    stack_push(s, 2);
    printf("\n%d data\n", s->data[s->top]);
    stack_push(s, 3);
    stack_push(s, 4);

    stack_print(s);
    printf("Popped num %d", stack_pop(s));
    stack_print(s);

    free(s);
    return 0;
}

Stack *stack_create(void) {
    Stack *s = malloc(sizeof(Stack));
    s->top = STACK_MAX;
    return s;
}

bool stack_is_full(Stack *s) {
    return s->top == -1;
}

bool stack_is_empty(Stack *s) {
    return s->top == STACK_MAX;
}

void stack_push(Stack *s, int value) {
    if (stack_is_full(s)) return;
    s->data[--s->top] = value;
}

int stack_pop(Stack *s) {
    return !stack_is_empty(s) ? s->data[s->top++] : -1;
}

int stack_peek(Stack *s) {
    return !stack_is_empty(s) ? s->data[s->top] : -1;
}

void stack_print(Stack *s) {
    if (stack_is_empty(s)) {
        printf("\nStack is Empty!\n");
        return;
    }
    printf("\nStack\n");
    for (int i = STACK_MAX - 1; i >= s->top; i--)
        printf("Index %d: %d\n", i, s->data[i]);
}
