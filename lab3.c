#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        return 1;
    }

    int n, m;
    if (fscanf(f, "%d %d", &n, &m) != 2) {
        fclose(f);
        return 1;
    }

    if (n <= 0 || m <= 0) {
        fclose(f);
        return 1;
    }

    int **a = malloc(n * sizeof(int*));
    if (!a) {
        fclose(f);
        return 1;
    }

    for (int i = 0; i < n; i++) {
        a[i] = malloc(m * sizeof(int));
        if (!a[i]) {
            for (int j = 0; j < i; j++) {
                free(a[j]);
            }
            free(a);
            fclose(f);
            return 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (fscanf(f, "%d", &a[i][j]) != 1) {
                for (int k = 0; k <= i; k++) {
                    free(a[k]);
                }
                free(a);
                fclose(f);
                return 1;
            }
        }
    }

    fclose(f);

    int s = 1;
    int k = n < m ? n : m;
    for (int i = 0; i < k; i++) {
        s *= a[i][i];
    }

    if (n < 3) {
        for (int i = 0; i < n; i++) free(a[i]);
        free(a);
        return 1;
    }

    int min = a[2][0];
    int min_j = 0;
    for (int j = 1; j < m; j++) {
        if (a[2][j] < min) {
            min = a[2][j];
            min_j = j;
        }
    }

    int tmp = a[2][min_j];
    a[2][min_j] = s;
    s = tmp;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    printf("%d\n", s);

    for (int i = 0; i < n; i++) free(a[i]);
    free(a);

    return 0;
}
