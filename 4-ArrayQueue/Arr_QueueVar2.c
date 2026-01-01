#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

typedef struct {
    int items[MAX];
    int front;
    int rear;
} Queue;

Queue *initialize();
bool isFull(Queue *Q);
bool isEmpty(Queue *Q);
void enqueue(Queue *Q, int value);
int dequeue(Queue *Q);
int peek(Queue *Q);
void display(Queue *Q);

int main() {
    Queue *Q = initialize();

    for (int i = 1; i <= 9; i++) {
        enqueue(Q, i);
    }

    printf("Front index: %d\n", Q->front);
    printf("Rear index: %d\n", Q->rear);

    enqueue(Q, 10);

    display(Q);

    printf("\nDequeued value: %d\n", dequeue(Q));
    display(Q);

    printf("\nFront value: %d\n", peek(Q));

    free(Q);
    return 0;
}

Queue *initialize() {
    Queue *Q = malloc(sizeof(Queue));
    Q->front = 0;
    Q->rear = -1;
    return Q;
}

bool isFull(Queue *Q) {
    return Q->front == (Q->rear + 2) % MAX;
}

bool isEmpty(Queue *Q) {
    return Q->front == (Q->rear + 1) % MAX;
}

void enqueue(Queue *Q, int value) {
    if (isFull(Q)) {
        printf("Queue is full\n");
        return;
    }

    Q->rear = (Q->rear + 1) % MAX;
    Q->items[Q->rear] = value;
}

int dequeue(Queue *Q) {
    if (isEmpty(Q)) {
        return -1;
    }

    int value = Q->items[Q->front];
    Q->front = (Q->front + 1) % MAX;
    return value;
}

int peek(Queue *Q) {
    return isEmpty(Q) ? -1 : Q->items[Q->front];
}

void display(Queue *Q) {
    if (isEmpty(Q)) {
        printf("\nQueue is empty\n");
        return;
    }

    int i = Q->front;
    printf("\nQueue contents:\n");

    while (true) {
        printf("%d ", Q->items[i]);
        if (i == Q->rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}
