#include <stdio.h>
#include <stdlib.h>

int calc_width(int w) {
    int n = 0;

    int area = 0;
    int piece_w = 0;
    int piece_l = 0;

    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        scanf("%d %d", &piece_w, &piece_l);
        area += piece_w * piece_l;
    }

    return area / w;
}

int main() {
    int w;

    while(scanf("%d", &w) && !feof(stdin))
        printf("%d\n", calc_width(w));
}