#ifndef KEEPER_H
#define KEEPER_H

#include "Base.h"
#include "FamilyMember.h"
#include <fstream>
#include <iostream>

void keeper_hello();

class Keeper
{
private:
    Base** members;
    int size;
    int capacity;
    void ensure_capacity();

public:
    Keeper();
    ~Keeper();

    void add(Base* obj);
    void remove(int index);
    void showAll() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    void clear();

    int getSize() const { return size; }
    Base* get(int i) const { return (i >= 0 && i < size) ? members[i] : nullptr; }
};

#endif // KEEPER_H
