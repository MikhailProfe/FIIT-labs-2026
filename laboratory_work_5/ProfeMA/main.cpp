#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

typedef unsigned int uint;

void swap(uint& a, uint& b) {
    uint t = a;
    a = b;
    b = t;
}

void fill_arr(uint* a, int n) {
    for (int i = 0; i < n; i++)
        a[i] = rand() % 1000;
}

void bubble_sort(uint* a, int n) {
    for (int i = 0; i < n; i++) {
        int f = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                swap(a[j], a[j + 1]);
                f = 1;
            }
        }
        if (f == 0) break;
    }
}

void merge(uint* a, uint* b, int n, int m, uint* c) {
    int j = 0, k = 0;
    for (int i = 0; i < n + m; i++) {
        if (j == n) { c[i] = b[k++]; }
        else {
            if (k == m) { c[i] = a[j++]; }
            else {
                if (a[j] < b[k]) { c[i] = a[j++]; }
                else { c[i] = b[k++]; }
            }
        }
    }
}
void mergeSort(uint* a, int n, uint* b) {
    if (n <= 1) return;
    mergeSort(&a[0], n / 2, &b[0]);
    mergeSort(&a[n / 2], n - n / 2, &b[n / 2]);
    merge(&a[0], &a[n / 2], n / 2, n - n / 2, &b[0]);
    for (int i = 0; i < n; i++) { a[i] = b[i]; }
}

uint get_max(uint* a, int n) {
    uint max = a[0];
    for (int i = 1; i < n; i++) {
        if (a[i] > max)
            max = a[i];
    }
    return max;
}

void counting_sort(uint* a, int n) {
    uint max = get_max(a, n);
    uint* count = (uint*)calloc(max + 1, sizeof(uint));
    uint* output = (uint*)malloc(sizeof(uint) * n);

    for (int i = 0; i < n; i++)
        count[a[i]]++;

    for (uint i = 1; i <= max; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[a[i]] - 1] = a[i];
        count[a[i]]--;
    }

    for (int i = 0; i < n; i++)
        a[i] = output[i];

    free(count);
    free(output);
}

int is_sorted(uint* a, int n) {
    for (int i = 0; i < n - 1; i++) {
        if (a[i] > a[i + 1]) return 0;
    }
    return 1;
}

void run_test(int n, int m) {
    printf("\nКол-во элементов | Время (сек)\n");
    printf("--------------------------------\n");
    int k = n;
    for (int i = 0; i < 5; i++) {
        uint* a = (uint*)malloc(sizeof(uint) * k);
        fill_arr(a, k);

        clock_t start = clock();
        if (m == 1) {
            bubble_sort(a, k);
        }
        else if (m == 2) {
            uint* b = (uint*)malloc(sizeof(uint) * k);
            mergeSort(a, k, b);
            free(b);
        }
        else if (m == 3) {
            counting_sort(a, k);
        }
        clock_t end = clock();

        if (is_sorted(a, k) == 0) {
            printf("Ошибка сортировки.\n");
        }

        double resTime = (double)(end - start) / CLOCKS_PER_SEC;

        printf("%-16d | %lf\n", k, resTime);
        k *= 5;
        free(a);
    }
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    srand(time(NULL));

    int n, m, again = 1;

    while (again == 1) {
        printf("Введите начальный размер массива (n > 0): ");
        scanf_s("%d", &n);
        if (n < 1) {
            printf("Ошибка: число должно быть натуральным!\n\n");
            continue;
        }

        printf("\nВыберите сортировку:\n");
        printf("1. Пузырьком\n");
        printf("2. Слиянием (MergeSort)\n");
        printf("3. Подсчетом (CountingSort)\n");
        printf("Ваш выбор: ");
        scanf_s("%d", &m);

        if (m < 1 || m > 3) {
            printf("Ошибка: введите число от 1 до 3!\n\n");
            continue;
        }

        run_test(n, m);

        printf("\nПовторить? (1 - да, 0 - нет): ");
        scanf_s("%d", &again);
        printf("\n");
    }
    return 0;
}