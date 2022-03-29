#include <stdio.h>
#include <stdlib.h>

/* A directed graph has an Eulerian trail if and only if at most one vertex has
   (out-degree) − (in-degree) = 1, at most one vertex has
   (in-degree) − (out-degree) = 1, every other vertex has equal in-degree and
   out-degree, and all of its vertices with nonzero degree belong to a single
   connected component of the underlying undirected graph. */

typedef struct intersection_st {
    int in, out;
} Intersection; 

int eulerian_trail(int n_i, int n_r) {
    int i, in, out;
    Intersection* intersections = calloc(n_i, sizeof(Intersection));

    /* read data */
    for(i = 0; i < n_r; i++) {
        scanf("%d %d", &out, &in);
        intersections[in].in++;
        intersections[out].out++;
    }

    int io_degree_1 = 0, oi_degree_1 = 0, deg_i = 0;

    /* calculate degrees for all vertices */
    for(i = 0; i < n_r; i++) {
        deg_i = intersections[i].out - intersections[i].in;
        if(deg_i != 0) {
            if(deg_i == 1) {
                io_degree_1++;
            }
            else if(deg_i == -1) {
                oi_degree_1++;
            }
            else { /* no trail if vertex has degree other than -1, 0, 1 */
                return 0;
            }
        }
    }

    /* no trail if more than 1 vertices with io_degree_1 or oi_degree_1 */
    if(io_degree_1 > 1 || oi_degree_1 > 1)
        return 0;

    free(intersections);
    
    return 1;

}

int main() {
    int n_i, n_r = 0;

    while(scanf("%d %d", &n_i, &n_r) == 2) {
        if(eulerian_trail(n_i, n_r))
            printf("Possible\n");
        else
            printf("Not possible\n");
    }

    return 0;
}