#include "Inout.h"
#include "GenCross.h"

using namespace Inout;
using namespace GenCross;


class Gens {
private:
    vector<string> Gen;
    Gencrossing Result;
protected:
    bool ExitGenCalc;
    int Seedling;
    char ex;

    void SendGenesForSeedling(int i) {
        cout << "Введите гены для саженца " << (i + 1) << ": ";
        Gen[i] = InOut.ReadGen(); // Сохраняем считанный ген в вектор
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
        InOut.PrintColoredGenes(Result.GCrossing(Seedling, Gen));
        cout << "\nВыйти в меню? [Y/N] :";
        cin >> ex;
        InOut.ClearInputStream();

        if (ex == 'Y' || ex == 'y') ExitGenCalc = true;
    }

    void Mistake(int i) {
        while (Gen[i].length() != 6) {
            cout << "!ОШИБКА!\nВы ввели " << Gen[i].length() << " ген\nПожалуйста, введите ровно 6 генов!\n";
            cout << "Введите гены для саженца " << (i + 1) << ": ";
            Gen[i] = InOut.ReadGen();
        }
    }

public:
    InputOutput InOut;
    void CalcGens()
    {
        ExitGenCalc = false;
        while (!ExitGenCalc)
        {
            InputNumSeedling();
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
protected:
    int menu;
    bool Exit;
    Texting texting;

    void InfoGenCrossing() {
        Calcgenes.InOut.PrintColoredGenes(texting.Text_info);
        cout << endl;
    }
public:
    Gens Calcgenes;
    void Options() {
        while (!Exit) {
            cout << texting.Text_menu;
            cin >> menu;
            cout << endl;
            // Проверяем, удалось ли считать целое число
            if (cin.fail()) {
                Calcgenes.InOut.ClearInputStream();
                cout << texting.Text_err_sedNumber << endl;
            } else {
                switch (menu) {
                    case 1: Exit = true;
                        break;
                    case 2:
                        InfoGenCrossing();
                        break;
                    case 3:
                        Calcgenes.InOut.ClearInputStream();
                        Calcgenes.CalcGens();
                        break;
                    case 4:
                        Calcgenes.InOut.SendCodePage();
                        break;
                    default:
                        cout << texting.Text_err_menuNum << endl;
                        break;
                }
            }
        }
    }
};

int main() {
    Menu menu;

    menu.Calcgenes.InOut.SetConsoleCodePage(CP_UTF8);
    setlocale(LC_ALL, "ru");
    SetConsoleTitle(TEXT("Gen Calculator"));

    menu.Options();

    return 0;
}