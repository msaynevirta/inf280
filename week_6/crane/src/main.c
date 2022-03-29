#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct coord_st {
    int x, y;
} Coord;

void print_coords(const Coord* coord, int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("%d, %d\n",coord[i].x, coord[i].y);
    }
}

int main() {
    int i, j, n_tests, n_coords;
    Coord* coords = NULL;

    scanf("%d", &n_tests);

    for(i = 0; i < n_tests; i++) {
        scanf("%d", &n_coords);

        /* read the coordinates and sort them by decreasing x*/
        coords = malloc(sizeof(Coord) * n_coords);
        for(j = 0; j < n_coords; j++) {
            scanf("%d %d", &coords[j].x, &coords[j].y);
        }

        printf("%.2f\n", 0);

        free(coords);
    }
    return 0;
}