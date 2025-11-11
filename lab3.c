#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Использование: %s <файл>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        printf("Не удалось открыть файл\n");
        return 1;
    }

    int n, m;
    fscanf(f, "%d %d", &n, &m);

    int **a = malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        a[i] = malloc(m * sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(f, "%d", &a[i][j]);
        }
    }

    fclose(f);

    int s = 1;
    int k = n < m ? n : m;
    for (int i = 0; i < k; i++) {
        s *= a[i][i];
    }

    if (n < 3) {
        printf("Матрица меньше 3 строк\n");
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

    printf("Матрица после изменений:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    printf("Новое значение S: %d\n", s);

    for (int i = 0; i < n; i++) free(a[i]);
    free(a);

    return 0;
}
