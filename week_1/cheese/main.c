#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ABS(N) ((N<0)?(-N):(N))
#define PI 3.14159265358979323846

void iterative_cutting(int n_h, int n_s) {
    double V_rem = 1e15;
    double s_curr, s_prev = 0; // start from z=0


    int* h_arr = malloc(2*n_h*sizeof(int));
    for(int i = 0; i < n_h; i++) {
        scanf("%d %*d %*d %d", &h_arr[(i*4)+0],
                               &h_arr[(i*4)+1]); // x, y ignored
    }
    // wanted slice volume
    double Vsg = V_rem / n_s;

    for(int i = 0; i < n_s; i++) { // calculate the slice thickness
        s_prev = s_curr; // in absolute coords

        double Vsh = V_rem / (n_s-i); // starting guess for volume based on remaning

        do { // refining
            // slice thickness guess
            double tsg = (2 * Vsg - Vsh) / 1e10;

            // calc new location
            s_curr += tsg;

            for(int j = 0; j < n_h ; j++) {
                double r = (double)h_arr[j*2+0];
                double z = (double)h_arr[j*2+1];
                double ca, cb, h = 0;

                if( (r-z > s_curr && r-z > s_prev) || (r+z < s_curr && r+z < s_prev) )
                    continue; // sphere not cutting the slice
                
                if(r+z < s_curr) { // kalotti takana
                    cb = s_prev - z;
                    h = z + r - s_prev;
                }

                else if(r-z > s_prev) { // kalotti edessä
                    ca = z - s_curr;
                    h = s_curr - z - r;
                }

                else {
                    cb = ABS(z - s_prev);
                    ca = ABS(z - s_curr);
                    h = tsg;
                }

                double a = (ca != 0 ? sqrt(r*r - ca*ca) : 0);
                double b = (cb != 0 ? sqrt(r*r - cb*cb) : 0);

                Vsh -= PI * h / 6.0 * (3*a*a*a + 3 *b*b*b + 3*h*h*h);
            }
        } while (Vsg - Vsh < 10e-6);

        printf("%f\n", s_curr - s_prev);
    }
    free(h_arr);
}

int main() {
    int n_h;
    int n_s;

    while(scanf("%d %d", &n_h, &n_s) && !feof(stdin))
        iterative_cutting(n_h, n_s);
}