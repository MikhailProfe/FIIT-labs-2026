#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "windows.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);

    int n;
    int bulls = 0;
    int cows = 0;
    int i, j, c;

    srand(time(NULL));

    printf("Введите длину числа (от 2 до 5): ");
    scanf_s("%d", &n);

    int* a = (int*) malloc(n * sizeof(int));
    int* b = (int*) malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        do {
            c = 0;
            a[i] = rand() % 10;

            if (i == 0 && a[i] == 0) {
                c = 1;
                continue;
            }

            for (j = 0; j < i; j++) {
                if (a[i] == a[j]) {
                    c = 1;
                    break;
                }
            }
        } while (c == 1);
    }

    printf("\nКомпьютер загадал: ");
    for (i = 0; i < n; i++) printf("%d", a[i]);
    printf("\n");

    while (bulls < n) {
        bulls = 0;
        cows = 0;
        int input;

        printf("Введите вашу попытку (число из %d цифр): ", n);
        scanf_s("%d", &input);

        for (i = n - 1; i >= 0; i--) {
            b[i] = input % 10;
            input = input / 10;
        }

        for (i = 0; i < n; i++) {
            for (j = 0; j < n; j++) {
                if (b[i] == a[j]) {
                    if (i == j) {
                        bulls++;
                    }
                    else {
                        cows++;
                    }
                }
            }
        }
        printf("Результат: cows = %d, bulls = %d\n\n", cows, bulls);
    }

    printf("Число отгадано.\n");

    free(a);
    free(b);

    return 0;
}