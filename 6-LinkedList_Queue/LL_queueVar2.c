#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Queue;

Queue *queue_create(void);
bool   queue_is_full(Queue *q);
bool   queue_is_empty(Queue *q);
void   queue_enqueue(Queue *q, int value);
int    queue_dequeue(Queue *q);
int    queue_front(Queue *q);
void   queue_print(Queue *q);
void   queue_clear(Queue *q);

int main(void) {
    Queue *q = queue_create();

    queue_enqueue(q, 1);
    queue_enqueue(q, 2);
    queue_enqueue(q, 3);

    printf("Front num is %d\n", queue_front(q));
    queue_print(q);

    printf("Dequeued num is %d\n", queue_dequeue(q));
    queue_print(q);

    queue_clear(q);
    free(q);
    return 0;
}

Queue *queue_create(void) {
    Queue *q = malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    return q;
}

bool queue_is_full(Queue *q) {
    (void)q;
    return false;
}

bool queue_is_empty(Queue *q) {
    return q->front == NULL;
}

void queue_enqueue(Queue *q, int value) {
    Node *n = calloc(1, sizeof(Node));
    n->data = value;
    n->next = NULL;

    if (queue_is_empty(q)) {
        q->front = q->rear = n;
    } else {
        q->rear->next = n;
        q->rear = n;
    }
}

int queue_dequeue(Queue *q) {
    if (queue_is_empty(q))
        return -1;

    Node *n = q->front;
    int num = n->data;

    q->front = q->front->next;
    if (q->front == NULL)
        q->rear = NULL;

    free(n);
    return num;
}

int queue_front(Queue *q) {
    return !queue_is_empty(q) ? q->front->data : -1;
}

void queue_print(Queue *q) {
    printf("Queue: ");
    Node *trav = q->front;
    while (trav != NULL) {
        printf("%d -> ", trav->data);
        trav = trav->next;
    }
    printf("NULL\n\n");
}

void queue_clear(Queue *q) {
    Node *trav = q->front;
    while (trav != NULL) {
        Node *next = trav->next;
        free(trav);
        trav = next;
    }
    q->front = q->rear = NULL;
}
