#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

typedef struct point_d_st {
    int x, y;
} Point_i;

typedef struct point_f_st {
    double x, y;
} Point_f;

typedef struct crane_st {
    Point_f centroid;
    int l, r, mass; /* left and right limits on x-axis */ 
} Crane;

void print_vertices(const Point_i* vertices, int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("%d, %d\n",vertices[i].x, vertices[i].y);
    }
}

void crane_cg(Crane* c, const Point_i* vertices, int n_vertices) {
    Point_f centroid_i = {0.0, 0.0};
    Point_i v0 = {0}, v1 = {0};
    int a = 0.0;
    int signed_a = 0.0;

    /* go around the edges */
    int i;
    for (i = 1; i < n_vertices; i++) {
        v0 = vertices[i-1];
        v1 = vertices[i];
        a = v0.x * v1.y - v1.x * v0.y;
        signed_a += a;
        centroid_i.x += (v0.x + v1.x) * a;
        centroid_i.y += (v0.y + v1.y) * a;
    }

    /* connect the start and end */
    v0 = vertices[i];
    v1 = vertices[0];
    a = v0.x * v1.y - v1.x * v0.y;
    signed_a += a;
    centroid_i.x += (v0.x + v1.x) * a;
    centroid_i.y += (v0.y + v1.y) * a;

    c->mass = signed_a;

    /* solve final divisions in floating point */
    Point_f centroid_f = {(double)centroid_i.x, (double)centroid_i.y};

    signed_a *= 0.5;
    centroid_f.x /= (6.0 * (double)signed_a);
    centroid_f.y /= (6.0 * (double)signed_a);

    c->centroid = centroid_f;
}

void crane_load(Crane* c, const Point_i* vertices, int n_vertices) {
    crane_cg(c, vertices, n_vertices);
    if(c->centroid.x > (double)c->l && c->centroid.x < (double)c->r) {
        printf("0 ... inf"); /* crane stable, cg between x axis limits */
    }
    else {
        /* formula for cg of two points with different weights */
        (cg_c * m_c + p_load * m_unknown ) / (m_unknown + m_c) = l; left limit mass
        c->centroid.x * c->mass + vertices[0].x * unknown_mass = c->r; left limit mass

        printf("%d ... %d", 0, 0);
    }
}

int comp_points (const void *p_1, const void *p_2) {
    const Point_i point_1 = *(const Point_i*)p_1;
    const Point_i point_2 = *(const Point_i*)p_2;

    if(point_1.x == point_2.x) {
        return (point_1.y > point_2.y);
    }
    return (point_1.x > point_2.x);
}

void polygon_base(Crane* c, const Point_i* vertices, int n_vertices) {
    Point_i* sorted_vertices = malloc(sizeof(Point_i) * n_vertices);
    memcpy(sorted_vertices, vertices, sizeof(Point_i) * n_vertices);

    qsort(sorted_vertices, n_vertices, sizeof(Point_i), comp_points);

    c->l = sorted_vertices[0].x;

    int i;
    for(i = 0; (sorted_vertices[i].y > 0 || i < n_vertices) ; i++) {
        c->r = sorted_vertices[i].x;
    }
}

int main() {
    int i, n_vertices;
    Crane c = {0};
    Point_i* vertices = NULL;

    while(scanf("%d", &n_vertices)) {
        /* read the coordinates */
        vertices = malloc(sizeof(Point_i) * n_vertices);
        for(i = 0; i < n_vertices; i++) {
            scanf("%d %d", &vertices[i].x, &vertices[i].y);
        }

        /* find the limits on x-axis */
        polygon_base(&c, vertices, n_vertices);

        /* check max possibe loading */
        crane_load(&c, vertices, n_vertices);

        putc('\n', stdout);
        print_vertices(vertices, n_vertices);

        free(vertices);
    }
    return 0;
}