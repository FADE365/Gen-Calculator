//
// Created by user on 30.01.2024.
//

#ifndef GENCALCULATOR_INOUT_H
#define GENCALCULATOR_INOUT_H

#include <iostream>
#include <windows.h>
#include <string>
#include <limits>
#include <conio.h>
#include <array>
#include <memory>

using namespace std;

namespace Inout {

    class Texting {
    public:
        string Text_menu =
                "Выберите опцию =>\n"
                "1. Выйти!\n"
                "2. Информация (Как скрещивать гены?)\n"
                "3. Калькулятор генов\n"
                "4. Display the code page of the console\n"
                "Введите номер опции : ";

        string Text_info =
                "Информация о скрещивании генов...\n"
                "В игре есть 5 генов.\n"
                "Из них 3 положительных (G, Y, H) и 2 отрицательных (W, X).\n\n"
                "G – ускоренный рост;\n"
                "Y – дополнительный урожай;\n"
                "H – устойчивость к условиям окружающей среды;\n"
                "W – увеличенное потребление воды;\n"
                "X – пустой ген.\n\n"
                "У генов условно есть колличество силы!\n"
                "У положительных генов (G, Y, H) - 60 силы.\n"
                "У отрицательных генов (W, X) - 100 силы.\n"
                "При скрещивании силы у одинаковых генов складываються, а ген у которого больше силы выживает.\n"
                "Если у генов одинаковое колличество силы то при срещивании может выжить один из них с вероятностью 50/50\n"
                "К примеру если у нас два гена G, и один ген X.\n"
                "В таком случае у гена G будет 120 силы так как их два, а у гена X будет 100 силы.\n"
                "Таким образом G > X по этому выживет ген G\n"
                "В ответе калькулятора в случае одинаковых генов, выведеться несколько вариантов генов в нужном месте это будет означать, "
                "что тут может быть этот ген с вероятностью 50/50\n ";

        string Text_err_sedNumber = "Ошибка: введите числовое значение.\n";
        string Text_err_menuNum = "Ошибка: введите число из списка опций!\n";

    };

    class InputOutput {
    protected:
        int red = 4;
        int green = 2;
        int white = 7;

        string exec(const char *cmd) {
            array<char, 128> buffer;
            string result;
            unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
            if (!pipe) {
                throw runtime_error("popen() failed!");
            }
            while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
                result += buffer.data();
            }
            return result;
        }

        void SetConsoleTextColor(WORD color) {
            setlocale(LC_ALL, "ru");
            HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hStdOut, color);
        }

    public:
        void SendCodePage() {
            try {
                string chcpResult = exec("chcp");
                SetConsoleTextColor(4);
                cout << "Current Code Page: " << chcpResult;
                SetConsoleTextColor(7);
            } catch (const exception &e) {
                cerr << "Error: " << e.what() << endl;
            }
        }

        void SetConsoleCodePage(unsigned int codepage) {
            SetConsoleOutputCP(codepage);
            SetConsoleCP(codepage);
        }

        void ClearInputStream() {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем поток ввода
            cin.clear(); // Сбрасываем любые ошибки ввода/вывода
        }

        void PrintColoredGenes(const string &genes) {
            for (char ch: genes) {
                if (ch == 'G' || ch == 'Y' || ch == 'H' || ch == 'g' || ch == 'y' || ch == 'h') {
                    SetConsoleTextColor(green); // Зелёный цвет для G, RY, H
                    cout << ch;
                } else if (ch == 'W' || ch == 'X' || ch == 'w' || ch == 'x') {
                    SetConsoleTextColor(red); // Красный цвет для W, X
                    cout << ch;
                } else {
                    SetConsoleTextColor(white); // Обычный цвет для остальных символов
                    cout << ch;
                }
            }
            SetConsoleTextColor(7); // Сброс цвета после вывода всех символов
            cout << endl; // Переход на новую строку после вывода строки
        }

        string ReadGen() {
            string input;
            char ch;
            while ((ch = _getch()) != '\r') { // Читаем символы до нажатия Enter
                if (ch == '\b' && !input.empty()) { // Обработка нажатия Backspace
                    cout << "\b \b";
                    input.pop_back();
                } else if (input.length() < 6 &&
                           (ch == 'G' || ch == 'Y' || ch == 'H' || ch == 'g' || ch == 'y' || ch == 'h' ||
                            ch == 'W' || ch == 'X' || ch == 'w' || ch == 'x')) {
                    // Установка соответствующего цвета в зависимости от символа
                    SetConsoleTextColor(
                            ch == 'G' || ch == 'Y' || ch == 'H' || ch == 'g' || ch == 'y' || ch == 'h' ? 2 : 4);
                    cout << ch;
                    SetConsoleTextColor(7); // Сброс на обычный цвет
                    input.push_back(ch);
                }
            }
            cout << endl; // Переход на новую строку после завершения ввода
            return input;
        }

    };
}

#endif //GENCALCULATOR_INOUT_H
