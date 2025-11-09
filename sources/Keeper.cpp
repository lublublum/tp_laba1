#include "Keeper.h"

void keeper_hello() {
    std::cout << "Keeper hello!\n";
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
        for (int i = 0; i < size; ++i) tmp[i] = members[i];
        delete[] members;
        members = tmp;
        capacity = newcap;
    }
}
void Keeper::add(Base* obj) {      // владеет obj (удалит в деструкторе)
    ensure_capacity();
    members[size++] = obj;
}
void Keeper::remove(int index) {   // удалить по индексу
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    delete members[index];
    for (int i = index; i < size -1; ++i){
        members[i] = members[i + 1];
    } 
    members[--size] = nullptr;
    std::cout << " Member removed \n";
}
void Keeper::showAll() const {
    for (int i = 0; i < size; i++) {
        std::cout << "========== Member number " << i+1 << " ==========\n";
        members[i]->show();
        std::cout << "\n";
    }

}

void Keeper::saveToFile(const std::string& filename) const {
    std::ofstream ofs(filename.c_str());
    if (!ofs){
        throw std::runtime_error("Cannot open file for writing");
    } 
    ofs << size << "\n";
    for (int i = 0; i < size; ++i) {
        // since only FamilyMember implemented, tag them
        ofs << "FM\n";
        members[i]->save(ofs);
    }
    ofs.close();
    std::cout << "Saved " << size << " members to " << filename << "\n";
}

void Keeper::loadFromFile(const std::string& filename) {
    std::ifstream ifs(filename.c_str());
    if (!ifs) {
        throw std::runtime_error("Cannot open file for reading");
    }
    clear();
    std::string line;
    std::getline(ifs, line);
    int cnt = std::stoi(line);
    for (int i = 0; i < cnt; ++i) {
        std::getline(ifs, line); // type tag
        if (line == "FM") {
            FamilyMember* fm = new FamilyMember();
            fm->load(ifs);
            add(fm);
        }
        else {
            throw std::runtime_error("Unknown type tag in file");
        }
    }
    ifs.close();
    std::cout << "Loaded " << size << " members from " << filename << "\n";
}

// очистить все и освободить память
void Keeper::clear() {
    for (int i = 0; i < size; ++i)
        delete members[i];
    delete[] members;
    members = nullptr;
    size = 0;
    capacity = 0;
}
