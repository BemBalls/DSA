#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

Stack *stack_create(void);
bool   stack_is_full(Stack *s);
bool   stack_is_empty(Stack *s);
void   stack_push(Stack *s, int value);
int    stack_pop(Stack *s);
int    stack_peek(Stack *s);
void   stack_print(Stack *s);
void   stack_clear(Stack *s);

int main(void) {
    Stack *s = stack_create();

    stack_print(s);
    stack_push(s, 1);
    stack_print(s);
    stack_push(s, 2);
    stack_push(s, 3);
    stack_print(s);

    printf("\nValue %d popped\n", stack_pop(s));
    printf("\nValue %d at top\n", stack_peek(s));
    stack_print(s);

    printf("\nValue %d popped\n", stack_pop(s));
    printf("\nValue %d popped\n", stack_pop(s));
    printf("\nValue %d popped\n", stack_pop(s));

    stack_clear(s);
    free(s);
    return 0;
}

Stack *stack_create(void) {
    Stack *s = malloc(sizeof(Stack));
    s->top = NULL;
    return s;
}

bool stack_is_full(Stack *s) {
    (void)s;
    return false;
}

bool stack_is_empty(Stack *s) {
    return s->top == NULL;
}

void stack_push(Stack *s, int value) {
    Node *n = malloc(sizeof(Node));
    n->data = value;
    n->next = s->top;
    s->top = n;
    printf("\nPushed %d\n", value);
}

int stack_pop(Stack *s) {
    if (stack_is_empty(s)) {
        printf("\nStack is Empty cannot POP\n");
        return -1;
    }
    Node *n = s->top;
    int value = n->data;
    s->top = n->next;
    free(n);
    return value;
}

int stack_peek(Stack *s) {
    if (stack_is_empty(s)) {
        printf("\nStack is empty cannot PEEK\n");
        return -1;
    }
    return s->top->data;
}

void stack_print(Stack *s) {
    if (stack_is_empty(s)) {
        printf("\nStack is empty cannot DISPLAY\n");
        return;
    }
    printf("\n--- Stack ---\n");
    Node *cur = s->top;
    while (cur != NULL) {
        printf("\nNode is %d\n", cur->data);
        cur = cur->next;
    }
}

void stack_clear(Stack *s) {
    Node *cur = s->top;
    while (cur != NULL) {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }
    s->top = NULL;
}
