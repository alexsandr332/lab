#include <stdio.h>
#include <limits.h>

int secondMax(int a[], int n, int i, int max1, int max2, int *hasSecondMax) {
    if (i == n) {
        if (max1 == max2 || *hasSecondMax == 0) {
            return INT_MIN;
        }
        return max2;
    }

    if (a[i] > max1) {
        max2 = max1;
        max1 = a[i];
        *hasSecondMax = 1;
    } else if (a[i] > max2 && a[i] < max1) {
        max2 = a[i];
        *hasSecondMax = 1;
    } else if (a[i] == max1 && a[i] != max2) {
        if (max1 != max2) {
            *hasSecondMax = 1;
        }
    } else if (max1 == max2 && a[i] < max1) {
        max2 = a[i];
        *hasSecondMax = 1;
    }

    return secondMax(a, n, i + 1, max1, max2, hasSecondMax);
}

int main() {
    int a[10];
    int n = 10;
    int num;
    char c;

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &num) != 1) {
            scanf("%c", &c);
            i--;
            continue;
        }
        a[i] = num;
    }

    if (n < 2) {
        return 1;
    }

    int max1 = a[0];
    int max2 = a[1] < a[0] ? a[1] : a[0];
    int hasSecondMax = 0;

    if (a[1] != a[0]) {
        hasSecondMax = 1;
        if (a[1] > a[0]) {
            max1 = a[1];
            max2 = a[0];
        } else {
            max1 = a[0];
            max2 = a[1];
        }
    }

    int res = secondMax(a, n, 2, max1, max2, &hasSecondMax);

    if (res == INT_MIN) {
        printf("No second maximum found.\n");
    } else {
        printf("%d\n", res);
    }

    return 0;
}
