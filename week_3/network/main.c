#include <stdio.h>
#include <stdlib.h>

/* queue */

typedef struct node {
    int v;
    struct node* next;
} Node;

typedef struct queue {
    Node *front, *back;
} Queue;

void enqueue(Queue *q, int v) {
    Node *n = malloc(sizeof(Node));
    n->v = v;
    n->next = NULL;

    q->back = n;
}

void dequeue(Queue* q) {
    Node *old = q->front;
    q->front = q->front->next;
    free(old);
}


/* find shortest path with bfs */

int bfs(int* edges, int n, int start) {
    int *visited = calloc(n, sizeof(int));

    Queue* q = {NULL, NULL};

    enqueue(q, ); /* queue root value */
    visited[start] = 1;

    while(q->front != NULL) {

    }
}

/* build graph from input & call dfs */

void least_intermediaries(int n_c, int n_p) {
    int i;

    /* read links */
    for (i = 0; i < n_p; i++) {
        scanf("%d %d %d", &x, &y, &w);
    }
}

int main() {
    int n_c, n_p, i = 0;

    scanf("%d", &n_c);

    for(i; i < n_c; i++) {
        scanf("%d", &n_p);
        least_intermediaries(n_p);
    }
    return 0;
}