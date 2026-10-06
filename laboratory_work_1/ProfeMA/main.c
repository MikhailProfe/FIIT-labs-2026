#include "stdio.h"
#include "windows.h"

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    printf("Введите глубину (50-90), ширину (80-120) и высоту (180-220) в сантиметрах:\n");
    double dvp = 0.5, dsp = 0.7, derevo = 0.8, d, w, h;
    double tzs = 0.5; // толщина задней стенки ДВП
    double tb_vnk = 1.5; // толщина боковин ДСП и верхней/нижней крышек ДСП
    double tnd = 1; // толщина накладных дверей ДЕРЕВО
    scanf_s("%lf %lf %lf", &d, &w, &h);
    if (h < 180 || h > 220 || d < 50 || d > 90 || w < 80 || w > 120) {
        printf("Неверные значения\n");
        return 1;
    }
    double v_zadn = h * w * tzs;
    double m_zadn = v_zadn * dvp;

    double v_bokovina = h * d * tb_vnk;
    double m_bokovina = 2 * v_bokovina * dsp;

    double v_kryshka = w * d * tb_vnk;
    double m_kryshka = 2 * v_kryshka * dsp;

    double v_dveri = h * w * tnd;
    double m_dveri = v_dveri * derevo;

    double v_polki = d * tb_vnk * (w - tb_vnk * 2);
    double m_polki;

    if(h <= 200.0) {
        
        m_polki = 4 * v_polki * dsp;
    }
    else {
        
        m_polki = 5 * v_polki * dsp;
    }
    double m = (m_zadn + m_bokovina + m_kryshka + m_dveri + m_polki) / 1000;
    printf("масса шкафа: %.3fкг", m);
}