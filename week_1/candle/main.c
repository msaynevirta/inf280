#include <stdio.h>

int iterative_candles(int d) {
    int c1 = 0;
    int c2 = 0;
    int n = 0;

    int yr; // starting year
    int yt;

    scanf("%d", &c1);
    scanf("%d", &c2);


    for(yt = 3; n <= c1+c2; yt++) {
        yr = yt + d;
        n = (yr * (yr + 1) / 2 - 10 ) + ( yt * (yt + 1) / 2 - 6); // candles
    }
    
    return c1 - ((yr * (yr + 1)) / 2 - 10);
}

int main() {
    int diff;

    while(scanf("%d", &diff) && !feof(stdin))
        printf("%d\n", iterative_candles(diff));
}