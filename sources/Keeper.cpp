#include "Keeper.h"

void keeper_hello() {
    std::cout << "\033[33mKeeper hello!\033[0m\n";
}

Keeper::Keeper() : members(nullptr), size(0), capacity(0) {
    std::cout << "\033[33mKeeper constructor called\033[0m\n";
}

Keeper::~Keeper() {
    clear();
    std::cout << "\033[33mKeeper destructor called\033[0m\n";
}

void Keeper::ensure_capacity() {
    if (capacity == 0) {
        capacity = 2;
        members = new Base * [capacity];
    }
    else if (size >= capacity) {
        int newcap = capacity * 2;
        Base** tmp = new Base * [newcap];
        for (int i = 0; i < size; ++i)
            tmp[i] = members[i];
        delete[] members;
        members = tmp;
        capacity = newcap;
    }
}

void Keeper::add(Base* obj) {
    ensure_capacity();
    members[size++] = obj;
}

void Keeper::remove(int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Неверный индекс");
    }
    delete members[index];
    for (int i = index; i < size - 1; ++i)
        members[i] = members[i + 1];
    members[--size] = nullptr;
}

void Keeper::showAll() const {
    if (size == 0) {
        std::cout << "Нет членов семьи.\n";
        return;
    }
    for (int i = 0; i < size; ++i) {
        std::cout << "\033[34m\n========= Член семьи #" << i + 1 << " =========\033[0m\n";
        members[i]->show();
    }
}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream ofs(filename.c_str());
    if (!ofs)
        throw std::runtime_error("Не удалось открыть файл для записи");

    ofs << size << "\n";
    for (int i = 0; i < size; ++i) {
        ofs << members[i]->getType() << "\n";
        members[i]->save(ofs);
    }
    ofs.close();
    std::cout << "\033[33mСохранено " << size << " объектов в " << filename << "\033[0m\n";
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename.c_str());
    if (!ifs)
        throw std::runtime_error("Не удалось открыть файл для чтения");

    clear();
    int count;
    ifs >> count;
    ifs.ignore();

    for (int i = 0; i < count; ++i) {
        std::string type;
        std::getline(ifs, type);
        if (type == "FamilyMember") {
            FamilyMember* fm = new FamilyMember();
            fm->load(ifs);
            add(fm);
        }
        else {
            throw std::runtime_error("Неизвестный тип объекта в файле");
        }
    }
    ifs.close();
    std::cout << "\033[33mЗагружено " << size << " объектов из " << filename << "\033[0m\n";
}

void Keeper::clear() {
    for (int i = 0; i < size; ++i)
        delete members[i];
    delete[] members;
    members = nullptr;
    size = 0;
    capacity = 0;
}
