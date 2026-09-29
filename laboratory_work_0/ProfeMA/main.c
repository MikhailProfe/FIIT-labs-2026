#include <stdio.h>
#include <math.h>
#include <windows.h>
int lab() {

	double x1, x2, y1, y2, r1, r2;

	printf("Введите координаты x, y и радиус r ПЕРВОЙ окружности:\n");
	scanf_s("%lf %lf %lf", &x1, &y1, &r1);
	printf("Введите координаты x, y и радиус r ВТОРОЙ окружности:\n");
	scanf_s("%lf %lf %lf", &x2, &y2, &r2);


	if (r1 <= 0 || r2 <= 0) {
		printf("Ошибка: один из радиусов меньше или равен нулю.\n");
		return 1;
	}

	double d = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));

	if (d == 0) {
		if (r1 == r2) {
			printf("Окружности полностью совпадают.\n");
		}
		else {
			printf("Окружности концентрические.\n"); //концентрические - один центр, но радиусы разные
		}
	}
	else if (d == r1 + r2) {
		printf("Окружности касаются снаружи в одной точке.\n");
	}
	else if (d == fabs(r1 - r2)) {
		printf("Окружности касаются изнутри в одной точке.\n");

	}
	else if (d > r1 + r2) {
		printf("Окружности не касаются и лежат отдельно.\n");
	}
	else if (d < fabs(r1 - r2)) {
		printf("Одна окружность лежит внутри другой и не касается.\n");
	}
	else {
		printf("Окружности пересекаются в двух точках.\n");
	}
	return 0;
}
int main() {
	SetConsoleOutputCP(65001);
	SetConsoleCP(65001);
	int q = lab();
	return q;
}