#include "headers/FamilyMember.h"
#include "headers/Keeper.h"
#include <iostream>

int main() {
    Keeper keeper;
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n--- Фамильное дерево ---\n";
        std::cout << "1. Добавить члена семьи\n";
        std::cout << "2. Показать всех\n";
        std::cout << "3. Удалить по индексу\n";
        std::cout << "4. Сохранить в файл\n";
        std::cout << "5. Загрузить из файла\n";
        std::cout << "0. Выход\n> ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }
        try {
            if (choice == 1) {
                std::cin.ignore();
                std::string name, birth, death;
                int age;
                std::cout << "ФИО: "; std::getline(std::cin, name);
                std::cout << "Дата рождения: "; std::getline(std::cin, birth);
                std::cout << "Дата смерти (или пусто): "; std::getline(std::cin, death);
                std::cout << "Возраст: "; std::cin >> age;
                FamilyMember* fm = new FamilyMember(name, birth, death, age);
                std::cin.ignore();
                // можно добавить родителей/детей/супруга сразу
                std::cout << "Добавить супруга? (y/n): ";
                char c; std::cin >> c; std::cin.ignore();
                if (c == 'y' || c == 'Y') {
                    std::string s;
                    std::cout << "ФИО супруга: "; std::getline(std::cin, s);
                    fm->setSpouse(s);
                }
                std::cout << "Сколько родителей добавить? "; int pc; std::cin >> pc; std::cin.ignore();
                for (int i = 0; i < pc; ++i) {
                    std::string p; std::cout << "Родитель " << i + 1 << ": "; std::getline(std::cin, p);
                    fm->addParent(p);
                }
                std::cout << "Сколько детей добавить? "; int cc; std::cin >> cc; std::cin.ignore();
                for (int i = 0; i < cc; ++i) {
                    std::string ch; std::cout << "Ребенок " << i + 1 << ": "; std::getline(std::cin, ch);
                    fm->addChild(ch);
                }

                keeper.add(fm);
            }
            else if (choice == 2) {
                keeper.showAll();
            }
            else if (choice == 3) {
                std::cout << "Индекс для удаления: ";
                int idx; 
                std::cin >> idx;
                keeper.remove(idx-1);
            }
            else if (choice == 4) {
                std::cout << "Имя файла: "; std::string fn; std::cin >> fn;
                keeper.saveToFile(fn);
            }
            else if (choice == 5) {
                std::cout << "Имя файла: "; std::string fn; std::cin >> fn;
                keeper.loadFromFile(fn);
            }
            else if (choice == 0) {
                std::cout << "Выход...\n";
            }
        }
        catch (const std::exception& ex) {
            std::cout << "Ошибка: " << ex.what() << "\n";
        }
    }

    return 0;
}
