#ifndef KEEPER_H
#define KEEPER_H

#include <iostream>
#include "Base.h"
#include <string>

void keeper_hello();


class Keeper {
private:
    Base** members;
    int size;
    int capacity;

    void ensure_capacity();

public:
    Keeper();
    ~Keeper();

    void add(Base* obj);      // владеет obj (удалит в деструкторе)
    void remove(int index);   // удалить по индексу
    void showAll() const;
    int getSize() const { return size; }

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    // очистить все и освободить память
    void clear();
};

#endif //KEEPER_H