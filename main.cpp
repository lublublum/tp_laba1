#include "FamilyMember.h"
#include "Keeper.h"
#include <iostream>

void showRelationshipMenu() {
    std::cout << "\n=== Управление связями ===\n";
    std::cout << "1. Установить родителей\n";
    std::cout << "2. Установить супруга\n";
    std::cout << "3. Добавить ребёнка\n";
    std::cout << "4. Очистить все связи\n";
    std::cout << "0. Назад\n> ";
}

int main() {
    Keeper keeper;
    int choice = -1;

    while (choice != 0) {
        std::cout << "\n--- Фамильное дерево ---\n";
        std::cout << "1. Добавить члена семьи\n";
        std::cout << "2. Показать всех\n";
        std::cout << "3. Удалить по индексу\n";
        std::cout << "4. Управление связями\n";
        std::cout << "5. Сохранить в файл\n";
        std::cout << "6. Загрузить из файла\n";
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
                std::cin.ignore();

                FamilyMember* fm = new FamilyMember(name, birth, death, age);
                keeper.add(fm);
                std::cout << "Член семьи добавлен!\n";
            }

            else if (choice == 2) {
                keeper.showAll();
            }

            else if (choice == 3) {
                std::cout << "Введите индекс для удаления: ";
                int idx;
                std::cin >> idx;
                keeper.remove(idx - 1);
                std::cout << "Удалено.\n";
            }

            else if (choice == 4) {
                if (keeper.getSize() < 2) {
                    std::cout << "Нужно минимум 2 человека.\n";
                    continue;
                }

                keeper.showAll();
                std::cout << "Выберите номер человека: ";
                int i;
                std::cin >> i;
                std::cin.ignore();

                FamilyMember* current = dynamic_cast<FamilyMember*>(keeper.get(i - 1));
                if (!current) {
                    std::cout << "Ошибка!\n";
                    continue;
                }

                int relChoice = -1;
                while (relChoice != 0) {
                    showRelationshipMenu();
                    std::cin >> relChoice;
                    std::cin.ignore();

                    if (relChoice == 1) {
                        int fi, mi;
                        keeper.showAll();
                        std::cout << "Отец (0 - нет): "; std::cin >> fi;
                        std::cout << "Мать (0 - нет): "; std::cin >> mi;
                        std::cin.ignore();
                        if (fi > 0 && fi <= keeper.getSize())
                            current->setFather(dynamic_cast<FamilyMember*>(keeper.get(fi - 1)));
                        if (mi > 0 && mi <= keeper.getSize())
                            current->setMother(dynamic_cast<FamilyMember*>(keeper.get(mi - 1)));
                    }

                    else if (relChoice == 2) {
                        keeper.showAll();
                        std::cout << "Выберите супруга: ";
                        int si;
                        std::cin >> si; std::cin.ignore();
                        if (si > 0 && si <= keeper.getSize())
                            current->setSpouse(dynamic_cast<FamilyMember*>(keeper.get(si - 1)));
                    }

                    else if (relChoice == 3) {
                        keeper.showAll();
                        std::cout << "Выберите ребёнка: ";
                        int ci;
                        std::cin >> ci; std::cin.ignore();
                        if (ci > 0 && ci <= keeper.getSize())
                            current->addChild(dynamic_cast<FamilyMember*>(keeper.get(ci - 1)));
                    }

                    else if (relChoice == 4) {
                        current->clearRelationships();
                        std::cout << "Все связи очищены.\n";
                    }

                    else if (relChoice == 0) break;
                    else std::cout << "Неверный выбор!\n";
                }
            }

            else if (choice == 5) {
                std::cout << "Имя файла: ";
                std::string fn;
                std::cin >> fn;
                keeper.saveToFile(fn);
            }

            else if (choice == 6) {
                std::cout << "Имя файла: ";
                std::string fn;
                std::cin >> fn;
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
