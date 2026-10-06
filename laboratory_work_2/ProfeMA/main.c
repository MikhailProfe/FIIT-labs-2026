#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "windows.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    srand(time(NULL));

    int z;
    printf("Выберите режим:\n");
    printf("1 - Компьютер загадывает, вы отгадываете\n");
    printf("2 - Вы загадываете, компьютер отгадывает\n");
    printf("Ваш выбор: ");
    scanf_s("%i", &z);

    switch (z) {
    case 1: {
        int target = rand() % 1000 + 1;
        int guess = 0;
        int i = 0;

        printf("\nЧисло загадано.\n");

        while (guess != target) {
            printf("Введите ваш вариант: ");
            scanf_s("%i", &guess);
            i++;

            if (guess < target) {
                printf("Загаданное число больше.\n");
            }
            else if (guess > target) {
                printf("Загаданное число меньше.\n");
            }
            else {
                printf("Угадали.\n");
            }
        }

        printf("Вы угадали число за %i попыток.\n", i);
        break;
    }

    case 2: {
        int low = 1;
        int high = 1000;
        int guess;
        int i = 0;
        char r;

        printf("Отвечайте символом '>' (если ваше число больше), '<' (если меньше) или '=' (если угадано).\n\n");

        while (low <= high) {
            guess = low + (high - low) / 2;
            i++;

            printf("Попытка %i. Компьютер думает, что это: %i\n", i, guess);
            printf("Ваш ответ (>, <, =): ");
            scanf_s(" %c", &r, 1);

            if (r == '>') {
                low = guess + 1;
            }
            else if (r == '<') {
                high = guess - 1;
            }
            else if (r == '=') {
                printf("Компьютер угадал ваше число.\n");
                break;
            }
            else {
                printf("Неверный символ.\n");
                i--;
            }
        }

        printf("Компьютер угадал число за %i попыток.\n", i);
        break;
    }

    default:
        printf("Неверный режим игры.\n");
        break;
    }
    return 0;
}