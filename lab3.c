#include <stdio.h>
#include <stdlib.h>
void bubble_sort(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Использование: %s <число1> <число2> ...\n", argv[0]);
        return 1;
    }

    int n = argc - 1;
    int numbers[n];
    for (int i = 0; i < n; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }

    bubble_sort(numbers, n);

    printf("Отсортированные числа:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}
