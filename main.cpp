#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <sstream>
#include <limits>
#include <conio.h>


using namespace std;

void SetConsoleTextColor(WORD color) {
    setlocale(LC_ALL, "ru");
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, color);
}

void SetConsoleCodePage(unsigned int codepage)
{
    SetConsoleOutputCP(codepage);
    SetConsoleCP(codepage);
}

void ClearInputStream() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем поток ввода
    cin.clear(); // Сбрасываем любые ошибки ввода/вывода
}


vector<int> find_max_indices(const int arr[], int size) {
    vector<int> max_indices;
    int max_value = numeric_limits<int>::min();

    // Находим максимальное значение
    for (int i = 0; i < size; ++i) {
        if (arr[i] > max_value) {
            max_value = arr[i];
        }
    }

    // Находим индексы всех элементов, равных максимальному значению
    for (int i = 0; i < size; ++i) {
        if (arr[i] == max_value) {
            max_indices.push_back(i);
        }
    }

    return max_indices;
}

void PrintColoredGenes(const string& genes) {
    for (char ch : genes) {
        if (ch == 'G' || ch == 'Y' || ch == 'H' || ch == 'g' || ch == 'y' || ch == 'h') {
            SetConsoleTextColor(2); // Зелёный цвет для G, Y, H
            cout << ch;
        } else if (ch == 'W' || ch == 'X' || ch == 'w' || ch == 'x') {
            SetConsoleTextColor(4); // Красный цвет для W, X
            cout << ch;
        } else {
            SetConsoleTextColor(7); // Обычный цвет для остальных символов
            cout << ch;
        }
    }
    SetConsoleTextColor(7); // Сброс цвета после вывода всех символов
    cout << endl; // Переход на новую строку после вывода строки
}

class Gencrossing {
public:
    string GCrossing(int Seedling, vector<string> Gen) {
        char charArray[5] = {'G', 'Y', 'H', 'W', 'X'};
        int intArray[5] = {0};
        vector<string> results; // Для хранения всех строк результатов

        for (int i = 0; i < 6; i++) {
            memset(intArray, 0, sizeof(intArray));
            for (int j = 0; j < Seedling; j++) {
                switch (Gen[j][i]) {
                    case 'G': case 'g': intArray[0] += 60; break;
                    case 'Y': case 'y': intArray[1] += 60; break;
                    case 'H': case 'h': intArray[2] += 60; break;
                    case 'W': case 'w': intArray[3] += 100; break;
                    case 'X': case 'x': intArray[4] += 100; break;
                    default: break;
                }
            }
            vector<int> max_indices = find_max_indices(intArray, 5);

            // Гарантируем, что есть достаточно строк для всех максимальных генов
            while (results.size() < max_indices.size()) {
                results.push_back(string(6, '-'));
            }

            // Заполняем строки максимальными генами
            for (size_t j = 0; j < max_indices.size(); ++j) {
                results[j][i] = charArray[max_indices[j]];
            }
        }

        string finalResult;
        for (const auto& line : results) {
            for (char ch : line) {
                finalResult += ch;
            }
            finalResult += "\n"; // Добавляем символ новой строки ПОСЛЕ каждой обработанной строки
        }
        return finalResult;
    }
};

class Gens {
private:
    vector<string> Gen;
    Gencrossing Result;
protected:
    bool YesNumSeedling, ExitGenCalc;
    int Seedling;
    char ex;
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
                SetConsoleTextColor(ch == 'G' || ch == 'Y' || ch == 'H' || ch == 'g' || ch == 'y' || ch == 'h' ? 2 : 4);
                cout << ch;
                SetConsoleTextColor(7); // Сброс на обычный цвет
                input.push_back(ch);
            }
        }
        cout << endl; // Переход на новую строку после завершения ввода
        return input;
    }

    void SendGenesForSeedling(int i) {
        cout << "Введите гены для саженца " << (i + 1) << ": ";
        Gen[i] = ReadGen(); // Сохраняем считанный ген в вектор
        cout << endl;
    }

    void InputNumSeedling() {
        string input;
        cout << "Введите количество Саженцев: ";
        while (true) {
            getline(cin, input); // Получаем строку от пользователя
            stringstream stream(input);
            if (stream >> Seedling) { // Пытаемся прочитать число
                if (Seedling > 0 && Seedling < 10) {
                    YesNumSeedling = true;
                    Gen.resize(Seedling);
                    break; // Выход из цикла, если число корректное
                }
            }
            cout << "!ОШИБКА!\nПожалуйста, введите количество Саженцев от 1 до 9.\n";
            cout << "Введите количество Саженцев: ";
        }
    }

    void EndGens() {
        cout << "Результат Генов:\n";
        PrintColoredGenes(Result.GCrossing(Seedling, Gen));
        cout << "\nВыйти в меню? Y/N :";
        cin >> ex;
        ClearInputStream();

        if (ex == 'Y' || ex == 'y') ExitGenCalc = true;
        else YesNumSeedling = false;
    }

    void Mistake(int i) {
        while (Gen[i].length() != 6) {
            cout << "!ОШИБКА!\nВы ввели " << Gen[i].length() << " ген\nПожалуйста, введите ровно 6 генов!\n";
            cout << "Введите гены для саженца " << (i + 1) << ": ";
            Gen[i] = ReadGen();
        }
    }

public:
    void CalcGens()
    {
        ExitGenCalc = false;
        YesNumSeedling = false;
        while (!ExitGenCalc)
        {
            while (!YesNumSeedling)
            {
                InputNumSeedling();
            }
            for (int i = 0; i < Seedling; i++)
            {
                SendGenesForSeedling(i);
                Mistake(i);
            }
            EndGens();
        }
    }
};

class Menu {
private:
    Gens Calcgenes;
protected:
    int menu;
    bool Exit;
    void InfoGenCrossing() {
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
        PrintColoredGenes(Text_info);
        cout << endl;
    }
public:
    void Options() {
        while (!Exit) {
            cout << "Выберите опцию =>\n"
                 << "1. Выйти!\n"
                 << "2. Информация (Как скрещивать гены?)\n"
                 << "3. Калькулятор генов\n"
                 << "Введите номер опции : ";
            cin >> menu;
            cout << endl;
            // Проверяем, удалось ли считать целое число
            if (cin.fail()) {
                ClearInputStream();
                cout << "Ошибка: введите числовое значение." << endl;
            } else {
                switch (menu) {
                    case 1: Exit = true;
                        break;
                    case 2:
                        InfoGenCrossing();
                        break;
                    case 3:
                        ClearInputStream();
                        Calcgenes.CalcGens();
                        break;
                    default:
                        cout << "Ошибка: введите число из списка опций!" << endl;
                        break;
                }
            }
        }
    }
};

int main() {
    SetConsoleCodePage(CP_UTF8);
    setlocale(LC_ALL, "ru");

    SetConsoleTitle(TEXT("Gen Calculator"));

    Menu menu;
    menu.Options();

    return 0;
}
