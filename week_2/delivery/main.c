#include <stdio.h>
#include <stdlib.h>

#define ABS(N) ((N<0)?(-N):(N))

typedef struct node {
    int x, y, cw, cost;
    struct node *l_child;
} Node;

Node* add_node(Node* curr, Node* next, const int c) {
    /* direct cost */
    int dx = curr->x - next->x;
    int dy = curr->y - next->y;

    int cost_dn = ABS(dx) + ABS(dy);

    /* home costs */
    int cost_ch = curr->x + curr->y;
    int cost_hn = next->x + next->y;

    /* Go via home if load too high / direct more costly */
    if(curr->cw + next->cw > c || (cost_dn > cost_ch && !(cost_ch == 0))) {
        Node* home = (Node*)calloc(1, sizeof(Node));
        home->cost = curr->cost + cost_ch;
        home->l_child = next;

        curr->l_child = home;

        next->cost = home->cost + cost_hn;
    }
    /* Otherwise go directly */
    else { 
        curr->l_child = next;

        next->cw += curr->cw;
        next->cost = curr->cost + cost_dn;
    }

    return next;
}

void free_tree(Node* curr) {
    Node* old;
    while(curr->l_child != NULL) {
        old = curr;
        curr = curr->l_child;
        free(old);
    }
    free(curr);
}

/* Cheapest route can be found by adding the positions to a bst search tree */
/* and getting the the cost at the leftmost leafnode */
void cheapest_route(int c, int n_p) {
    int x, y, w, i = 0;

    Node* root = (Node*)calloc(1, sizeof(Node));
    Node* curr = root;

    /* read package data */
    for (i = 0; i < n_p; i++) {
        scanf("%d %d %d", &x, &y, &w);
        Node* next = (Node*)calloc(1, sizeof(Node));
        next->cw = w;
        next->x = x;
        next->y = y; 
        curr = add_node(curr, next, c);
    }
    curr = add_node(curr, (Node*)calloc(1, sizeof(Node)), c); /* return home */
    printf("\n%d\n", curr->cost);

    free_tree(root);
}

int main() {
    int i, c, n_c, n_p = 0;
    scanf("%d", &n_c);

    for(i = 0; i < n_c; i++) {
        scanf("%d", &c);
        scanf("%d", &n_p);

        cheapest_route(c, n_p);
    }
    return 0;
}