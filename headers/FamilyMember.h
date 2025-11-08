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

    std::string* children;
    int children_count;
 
    std::string spouse;

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

    void setBirthDate(const std::string& date);
    std::string getBirthDate() const;

    void setDeathDate(const std::string& date);
    std::string getDeathDate() const;

    void setAge(const int age);
    int getAge() const;

    void addParent(const std::string& p);
    std::string getParents() const;

    void addChild(const std::string& c);
    std::string getChild() const;

    void setSpouse(const std::string& s);
    std::string getSpouse() const;

    // Реализация Base
    void show() const override;
    void edit() override;
    void save(std::ostream& os) const override;
    void load(std::istream& is) override;
};


#endif //FAMILY_MEMBER_H