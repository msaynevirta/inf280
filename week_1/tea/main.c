#include <stdio.h>

int n_true(int orig) {
    
    int arr[5] = {0};
    int n_true = 0;

    
    scanf("%d %d %d %d %d", &arr[0], &arr[1], &arr[2], &arr[3], &arr[4]);

    for(int i = 0; i < 5; i++) {
        n_true += orig == arr[i];
    }

    return n_true;
}

int main() {
    int orig = 0;

    while(scanf("%d", &orig) && !feof(stdin))
        printf("%d\n", n_true(orig));
}