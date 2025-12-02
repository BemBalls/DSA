#include <stdio.h>

#define MAX_PROCESSES 100

typedef struct {
    int priority;   // Higher number = higher priority
} Process;

typedef struct {
    Process heap[MAX_PROCESSES];
    int size;      // current number of elements
    int capacity;  // maximum capacity
} PriorityQueue;

/* ----- Utility: swap two processes ----- */
void swap(Process *a, Process *b) {
    Process temp = *a;
    *a = *b;
    *b = temp;
}

/* ----- Heapify (down-heapify) starting at index i ----- */
void heapify(PriorityQueue *pq, int i) {
    int largest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < pq->size && pq->heap[left].priority > pq->heap[largest].priority) {
        largest = left;
    }

    if (right < pq->size && pq->heap[right].priority > pq->heap[largest].priority) {
        largest = right;
    }

    if (largest != i) {
        swap(&pq->heap[i], &pq->heap[largest]);
        heapify(pq, largest);
    }
}

/* ----- Enqueue: insert new process with given priority ----- */
void enqueue(PriorityQueue *pq, int priority) {
    if (pq->size == pq->capacity) {
        printf("Priority queue is full!\n");
        return;
    }

    // 1) Insert at last available index
    int i = pq->size;
    pq->heap[i].priority = priority;
    pq->size++;

    // 2) Up-heapify (bubble up)
    while (i != 0) {
        int parent = (i - 1) / 2;
        if (pq->heap[i].priority > pq->heap[parent].priority) {
            swap(&pq->heap[i], &pq->heap[parent]);
            i = parent;
        } else {
            break;
        }
    }
}

/* ----- Dequeue: remove and return max-priority process ----- */
Process dequeue(PriorityQueue *pq) {
    Process dummy = { -1 };   // for error cases

    if (pq->size == 0) {
        printf("Priority queue is empty!\n");
        return dummy;
    }

    // Root is max
    Process root = pq->heap[0];

    // 1) Move last element to root, shrink size
    pq->heap[0] = pq->heap[pq->size - 1];
    pq->size--;

    // 2) Heapify from root down
    heapify(pq, 0);

    return root;
}

/* ----- Helper: print current heap array ----- */
void printPQ(PriorityQueue *pq) {
    printf("Heap array (priority only): ");
    for (int i = 0; i < pq->size; i++) {
        printf("%d ", pq->heap[i].priority);
    }
    printf("\n");
}

int main(void) {
    PriorityQueue pq;
    pq.size = 0;
    pq.capacity = MAX_PROCESSES;

    // Example usage
    enqueue(&pq, 5);
    enqueue(&pq, 3);
    enqueue(&pq, 10);
    enqueue(&pq, 1);
    enqueue(&pq, 8);

    printPQ(&pq);

    Process p = dequeue(&pq);
    printf("Dequeued max priority: %d\n", p.priority);
    printPQ(&pq);

    p = dequeue(&pq);
    printf("Dequeued max priority: %d\n", p.priority);
    printPQ(&pq);

    return 0;
}