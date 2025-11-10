#ifndef FAMILY_MEMBER_H
#define FAMILY_MEMBER_H

#include "Base.h"
#include <iostream>
#include <string>

void family_hello();

class FamilyMember : public Base
{
private:
    std::string full_name;
    std::string date_of_birth;
    std::string date_of_death;
    int age;

    // иерархические связи между объектами
    FamilyMember* father;
    FamilyMember* mother;
    FamilyMember* spouse;
    FamilyMember** children;
    int childrenCount;
    int childrenCapacity;

public:
    // Конструкторы и оператор
    FamilyMember();
    FamilyMember(const std::string& name, const std::string& birth,
        const std::string& death, int age);
    FamilyMember(const FamilyMember& other);
    FamilyMember& operator=(const FamilyMember& other);
    ~FamilyMember();

    // --- базовые поля ---
    void setName(const std::string& name);
    std::string getName() const;

    void setBirthDate(const std::string& date);
    std::string getBirthDate() const;

    void setDeathDate(const std::string& date);
    std::string getDeathDate() const;

    void setAge(int age);
    int getAge() const;

    // --- объектные связи ---
    void setFather(FamilyMember* f, bool updateReverse = true);
    void setMother(FamilyMember* m, bool updateReverse = true);
    void setSpouse(FamilyMember* s, bool updateReverse = true);
    void addChild(FamilyMember* c, bool updateReverse = true);
    void removeChild(FamilyMember* c, bool updateReverse = true);
    void clearRelationships();
    void showRelations() const;

    // --- реализация виртуальных методов Base ---
    void show() const override;
    void edit() override;
    void save(std::ostream& os) const override;
    void load(std::istream& is) override;
    const char* getType() const override { return "FamilyMember"; }
};

#endif // FAMILY_MEMBER_H
