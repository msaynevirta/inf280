#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct coord_st {
    int x, y;
} Coord;

int comp_x ( const void * coord_1, const void * coord_2 ) {
    return ((const Coord*)coord_1)->x < ((const Coord*)coord_2)->x;
}

void print_coords(const Coord* coord, int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("%d, %d\n",coord[i].x, coord[i].y);
    }
}

double sunny_side(const Coord* coords, int n_coords) {
    double sunny = 0;
    int i;
    int max_y = coords[0].y;

    Coord old, new;

    for(i = 1; i < n_coords; i++) {
        if(coords[i].y > max_y) {
            old = coords[i-1];
            new = coords[i];

            int tot_y = new.y - old.y;
            int sunny_y = new.y - max_y;

            sunny += sqrt( (old.x - new.x) * (old.x - new.x) +
                           (old.y - new.y) * (old.y - new.y) )
                     * (double)sunny_y / (double)tot_y;
            
            max_y = new.y;
        }
    }
    return sunny;
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

        qsort(coords, n_coords, sizeof(Coord), comp_x);

        printf("%.2f\n", sunny_side(coords, n_coords));

        free(coords);
    }
    return 0;
}