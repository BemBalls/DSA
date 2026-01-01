#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Queue;

Queue *initialize();
bool isEmpty(Queue *q);
void enqueue(Queue *q, int value);
int dequeue(Queue *q);
int peek(Queue *q);
void display(Queue *q);

int main() {
    Queue *q = initialize();

    enqueue(q, 1);
    display(q);

    enqueue(q, 2);
    enqueue(q, 3);
    enqueue(q, 4);
    display(q);

    printf("\n%d is at front\n", peek(q));

    printf("\nDequeued %d\n", dequeue(q));
    display(q);

    printf("\nDequeued %d\n", dequeue(q));
    display(q);

    enqueue(q, 5);
    display(q);

    printf("\nDequeued %d\n", dequeue(q));
    printf("\nDequeued %d\n", dequeue(q));
    printf("\nDequeued %d\n", dequeue(q));

    display(q);

    free(q);
    return 0;
}

Queue *initialize() {
    Queue *q = malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

bool isEmpty(Queue *q) {
    return q->front == NULL;
}

void enqueue(Queue *q, int value) {
    Node *newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (isEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

int dequeue(Queue *q) {
    if (isEmpty(q)) {
        return -1;
    }

    Node *temp = q->front;
    int value = temp->data;
    q->front = temp->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return value;
}

int peek(Queue *q) {
    return isEmpty(q) ? -1 : q->front->data;
}

void display(Queue *q) {
    if (isEmpty(q)) {
        printf("\nEmpty List\n");
        return;
    }

    Node *temp = q->front;
    printf("\n--- List ---\n");
    while (temp) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
