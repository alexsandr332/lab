#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sizes[] = {10, 1000, 10000, 100000};
int count = 4;

void bubble(int *a, int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (a[j] > a[j+1]) {
                int t = a[j];
                a[j] = a[j+1];
                a[j+1] = t;
            }
}

void insert(int *a, int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i-1;
        while (j >= 0 && a[j] > key) {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }
}

void selection(int *a, int n) {  // ИЗМЕНИЛ НАЗВАНИЕ ЗДЕСЬ
    for (int i = 0; i < n-1; i++) {
        int min = i;
        for (int j = i+1; j < n; j++)
            if (a[j] < a[min])
                min = j;
        int t = a[i];
        a[i] = a[min];
        a[min] = t;
    }
}

double test(void (*sort)(int*, int), int size) {
    int *arr = malloc(size * sizeof(int));
    
    for (int i = 0; i < size; i++)
        arr[i] = rand();
    
    clock_t start = clock();
    sort(arr, size);
    clock_t end = clock();
    
    for (int i = 0; i < size-1; i++)
        if (arr[i] > arr[i+1]) {
            printf("Ошибка!\n");
            break;
        }
    
    free(arr);
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL));
    
    printf("Размер | Пузырек | Вставками | Выбором\n");
    printf("-------|----------|-----------|--------\n");
    
    for (int i = 0; i < count; i++) {
        int size = sizes[i];
        
        double t1 = test(bubble, size);
        double t2 = test(insert, size);
        double t3 = test(selection, size);  // И ЗДЕСЬ ИЗМЕНИЛ
        
        if (size == 10)
            printf("    10 | %7.6f |  %7.6f  | %7.6f\n", t1, t2, t3);
        else if (size == 1000)
            printf("  1000 | %7.3f |  %7.3f  | %7.3f\n", t1, t2, t3);
        else if (size == 10000)
            printf(" 10000 | %7.3f |  %7.3f  | %7.6f\n", t1, t2, t3);
        else
            printf("100000 | %7.3f |  %7.3f  | %7.3f\n", t1, t2, t3);
    }
    
    return 0;
}
