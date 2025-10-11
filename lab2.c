#include <stdio.h>

int secondMax(int a[], int n, int i, int max1, int max2) {
    if (i == n) return max2; // когда дошли до конца — возвращаем второй максимум

    if (a[i] > max1) {
        max2 = max1;
        max1 = a[i];
    } else if (a[i] > max2 && a[i] < max1) {
        max2 = a[i];
    }

    return secondMax(a, n, i + 1, max1, max2);
}

int main() {
    int a[10];
    int n = 10;

    printf("Введите 10 чисел:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int max1 = a[0];
    int max2 = a[0];

    int res = secondMax(a, n, 0, max1, max2);

    printf("Второй максимум: %d\n", res);

    return 0;
}
