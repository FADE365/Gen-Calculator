//
// Created by user on 30.01.2024.
//

#ifndef GENCALCULATOR_GENCROSS_H
#define GENCALCULATOR_GENCROSS_H

#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <limits>
#include <sstream>

using namespace std;

namespace GenCross {
    class Gencrossing {

    protected:
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
}

#endif //GENCALCULATOR_GENCROSS_H
