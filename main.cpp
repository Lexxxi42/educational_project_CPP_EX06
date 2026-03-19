#include <iostream>
#include <math.h>
#include <string>
#define SIZE 30
using namespace std;

int t_1() {
    float F[SIZE] {0};
    float START, STOP, STEP = 0;

    try {
        printf("Введите начальное значение: ");
        if (scanf("%f", &START) != 1.0) throw runtime_error("введите действительные числа.");

        printf("Введите конечное значение: ");
        if (scanf("%f", &STOP) != 1.0) throw runtime_error("введите действительные числа.");
        if (STOP <= START) throw runtime_error("конечное значение должно быть больше начального");

        printf("Введите шаг: ");
        if (scanf("%f", &STEP) != 1.0) throw runtime_error("введите действительные числа.");

        if (fabs(STEP) < 1e-6 || STEP < 0) throw runtime_error("шаг не может быть меньше либо равен 0");
        
        int points = (STOP - START) / STEP + 1;
        if (points < SIZE) throw runtime_error("отрезок содержит недостаточно точек");
        else if (points > SIZE) printf("Предупреждение: отрезок содержит %d точек, но будет обработано только %d.\n", points, SIZE);
        
        float last_positive = 0.0;
        for (int i = 0; i < SIZE; i++) {
            float x = START + i * STEP;
            F[i] = exp(-x) * sin(6 * x);
            if (F[i] > 0) last_positive = F[i];
        }
        
        if (last_positive <= 0) throw runtime_error("нет положительных значений функции.");
        
        for (int i = 0; i < SIZE; i++) {
            F[i] /= last_positive;
            printf("F[%d] = %.7f\n", i, F[i]);
        }
    }
    catch (exception& e) {
        cout << "Ошибка: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
// a b c - в любой аргумент на входе
// 1 2 0.000000001
// 1 1 1
// 1 2 -2

// 0 29 1
// 0 2.9 0.1
// -1 1.9 0.1
// 0 14.5 0.5
// 0 0.29 0.01
// 0.01 0.02 0.0001

int t_2() {
    string str;
    string start_str = "<strong>";
    string end_str = "</strong>";
    
    try {
        printf("Введите строку для обработки: ");
        getline(cin, str);
        
        if (str.empty()) throw runtime_error("строка пустая");

        int pos = 0;
        int found = 0;
        
        while(true) {
            int is_start = str.find(start_str, pos);
            if(is_start == -1) break;

            int is_end = str.find(end_str, is_start + start_str.length());
            if(is_end == -1) break;

            found = 1;
            int name_start = is_start + start_str.length();
            int name_length = is_end - name_start;
            
            if (name_length <= 0) throw runtime_error("строка в теге пустая");

            cout << "ФИО героя: " << str.substr(name_start, name_length) << endl;

            pos = is_end + end_str.length();
        }
        
        if(!found) throw runtime_error("строка не содержит выделенных данных о героях ВОВ.");
    }
    catch (const exception& e) {
        cout << "Ошибка: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
int main() {
    t_1();
    t_2();
    return 0;
}
// <strong>Иванов</strong>
// 	Иван <strong>Петров</strong> и <strong>Сидоров</strong>
// <strong>Иванов</strong> <strong>Петров</strong>
// text<strong>Иван</strong>text<strong>Петр</strong>text
// <>strong>Иван</strong>
// <strong>Иван Петрович Сидоров</strong>
// <strong>Иван123</strong>
// Исключения 
// <strong>Иванов
// Петров</strong>
// <strong></strong>