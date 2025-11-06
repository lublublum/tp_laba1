#ifndef FAMILY_MEMBER_H
#define FAMILY_MEMBER_H

#include <iostream>
#include "Base.h"
#include <string>

void family_hello();

class FamilyMember : public Base
{
private:
    std::string full_name;
    std::string date_of_birth;
    std::string date_of_death;
    int age;
    // ручные динамические массивы (без STL контейнеров)
    std::string* parents;
    int parents_count;
    int parents_capacity;

    std::string spouse;

    std::string* children;
    int children_count;
    int children_capacity;

    void ensure_parents_capacity();
    void ensure_children_capacity();

public:
    FamilyMember() = default;
    FamilyMember(const std::string& name, const std::string& birth, 
                 const std::string& death, int age);
    FamilyMember(const FamilyMember& other);
    FamilyMember& operator=(const FamilyMember& other);
    ~FamilyMember() override;

    // set/get
    void setName(const std::string& name);
    std::string getName() const;

    void addParent(const std::string& p);
    void addChild(const std::string& c);
    void setSpouse(const std::string& s);

    // Реализация Base
    void show() const override;
    void edit() override;
    void save(std::ostream& os) const override;
    void load(std::istream& is) override;
};


#endif //FAMILY_MEMBER_H