#include <windows.h>
#include <stdio.h>
#include <string.h>

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    char codes[5][5] = { "1111", "2222", "3333", "4444", "5555" };
    char names[5][50] = { "Игровая мышь", "Механическая клавиатура", "Беспроводные наушники", "Коврик для мыши XL", "Внешний жесткий диск" };
    int prices[5] = { 2500, 5500, 3900, 1200, 6000 };
    int discs[5] = { 10, 15, 5, 50, 20 };

    int ck_idx[5] = { 0 };
    int ck_qty[5] = { 0 };
    int ck_n = 0;

    int menu = 0;
    int scan_i = -1;

    while (1) {
        printf("\n=== СИСТЕМА: ЭЛЕКТРОННАЯ КАССА ===\n");
        printf("1. Сканировать очередной товар\n");
        printf("2. Вывести описание отсканированного товара\n");
        printf("3. Добавить данные о товаре в чек\n");
        printf("4. Сформировать чек за покупку\n");
        printf("5. Рассчитать итоговую сумму к оплате\n");
        printf("Выберите действие (1-5): ");

        if (scanf_s("%d", &menu) != 1) {
            printf("Ошибка ввода! Пожалуйста, введите цифру.\n");
            while (getchar() != '\n');
            continue;
        }

        if (menu == 5) {
            break;
        }

        switch (menu) {
        case 1:
        {
            printf("\n[Выполняется сканирование...]\n");
            char tmp[20];
            printf("Введите 4-значный штрих-код: ");
            scanf_s("%s", tmp, (unsigned int)sizeof(tmp));

            int found = -1;

            for (int i = 0; i < 5; i++) {
                if (strcmp(codes[i], tmp) == 0) {
                    found = i;
                    break;
                }
            }

            if (found != -1) {
                scan_i = found;
                printf("Товар успешно отсканирован!\n");
            }
            else {
                printf("Ошибка: Товар с таким штрих-кодом не найден.\n");
            }
        }
        break;

        case 2:
            printf("\n[Запрос описания товара...]\n");
            if (scan_i == -1) {
                printf("Сначала отсканируйте товар (Пункт 1)!\n");
            }
            else {
                printf("Описание товара:\n");
                printf("Название: %s\n", names[scan_i]);
                printf("Цена за единицу: %d руб.\n", prices[scan_i]);
                printf("Скидка на товар: %d%%\n", discs[scan_i]);
            }
            break;

        case 3:
            printf("\n[Добавление в чек...]\n");
            if (scan_i == -1) {
                printf("Нечего добавлять. Сначала отсканируйте товар (Пункт 1).\n");
            }
            else {
                int already_in = -1;
                for (int j = 0; j < ck_n; j++) {
                    if (ck_idx[j] == scan_i) {
                        already_in = j;
                        break;
                    }
                }

                if (already_in != -1) {
                    ck_qty[already_in]++;
                    printf("Количество товара '%s' увеличено до %d шт.\n", names[scan_i], ck_qty[already_in]);
                }
                else {
                    ck_idx[ck_n] = scan_i;
                    ck_qty[ck_n] = 1;
                    ck_n++;
                    printf("Товар '%s' добавлен в чек (1 шт.).\n", names[scan_i]);
                }

                scan_i = -1;
            }
            break;

        case 4:
            printf("\n[Генерация промежуточного чека...]\n");
            if (ck_n == 0) {
                printf("Ваш чек пока пуст. Добавьте товары (Пункт 3).\n");
            }
            else {
                printf("\n--- ТЕКУЩИЙ ЧЕК ---\n");
                for (int i = 0; i < ck_n; i++) {
                    int idx = ck_idx[i];
                    int total_p = prices[idx] * ck_qty[i];

                    printf("%s – %d руб. – %d шт. – %d руб.\n",
                        names[idx], prices[idx], ck_qty[i], total_p);
                }
                printf("--------------------\n");
            }
            break;
        }
    }

    printf("\n===================================\n");
    printf("        ИТОГОВЫЙ ЧЕК ЗА ПОКУПКУ    \n");
    printf("===================================\n");

    if (ck_n == 0) {
        printf("Вы вышли из программы, ничего не купив.\n");
    }
    else {
        int sum_no_d = 0;
        int sum_disc = 0;
        int total_pay = 0;

        for (int i = 0; i < ck_n; i++) {
            int idx = ck_idx[i];

            int item_p = prices[idx];
            int item_q = ck_qty[i];
            int item_d = discs[idx];

            int total_item_p = item_p * item_q;
            int item_d_rub = (total_item_p * item_d) / 100;

            sum_no_d += total_item_p;
            sum_disc += item_d_rub;

            printf("%s – %d руб. – %d шт. – %d руб.\n",
                names[idx], item_p, item_q, total_item_p);
        }

        total_pay = sum_no_d - sum_disc;

        printf("-----------------------------------\n");
        printf("Стоимость товаров без скидки: %d руб.\n", sum_no_d);
        printf("Суммарная скидка по чеку:     %d руб.\n", sum_disc);
        printf("ИТОГОВАЯ СУММА К ОПЛАТЕ:      %d руб.\n", total_pay);
    }
    printf("===================================\n");
    printf("Спасибо за покупку! До свидания.\n");
    return 0;
}