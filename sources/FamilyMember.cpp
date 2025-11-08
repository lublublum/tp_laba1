#include "FamilyMember.h"

void family_hello() {
    std::cout << "Family hello!\n";
}

FamilyMember::FamilyMember(const std::string& name, const std::string& birth,
    const std::string& death, int age) :
    full_name(name), date_of_birth(birth),
    date_of_death(death), age(age),
    parents(nullptr), parents_count(0),
    children(nullptr), children_count(0),
    spouse("")
{
    std::cout << "Famili constructor called\n";
}
FamilyMember::FamilyMember(const FamilyMember& other) :
    full_name(other.full_name), date_of_birth(other.date_of_birth),
    date_of_death(other.date_of_death), age(other.age),
    parents_count(other.parents_count), children_count(other.children_count),
    spouse(other.spouse), parents(nullptr), children(nullptr)
{
    if (parents_count > 0) {
        parents = new std::string[parents_count];
        for (int i = 0; i < parents_count; i++) {
            parents[i] = other.parents[i];
        }
    }

    if (children_count > 0)
    {
        children = new std::string[children_count];
        for (int i = 0; i < children_count; i++) {
            children[i] = other.children[i];
        }
    }
    std::cout << "Famili copy constructor called\n";
}
FamilyMember& FamilyMember::operator=(const FamilyMember& other) {
    if (this == &other) return *this;
    // освобождаем старое
    delete[] parents;
    delete[] children;

    full_name = other.full_name;
    date_of_birth = other.date_of_birth;
    date_of_death = other.date_of_death;
    age = other.age;
    spouse = other.spouse;

    parents_count = other.parents_count;
    if (parents_count > 0) {
        parents = new std::string[parents_count];
        for (int i = 0; i < parents_count; i++) {
            parents[i] = other.parents[i];
        }
    }

    children_count = other.children_count;
    if (children_count > 0)
    {
        children = new std::string[children_count];
        for (int i = 0; i < children_count; i++) {
            children[i] = other.children[i];
        }
    }

    std::cout << "FamilyMember assignment operator called for " << full_name << "\n";
    return *this;
}
FamilyMember::~FamilyMember() {
    delete[] parents;
    delete[] children;
    std::cout << "FamilyMember destructor called for " << full_name << "\n";
}

// set / get
void FamilyMember::setName(const std::string& name) { full_name = name; }
std::string FamilyMember::getName() const { return full_name; }

void FamilyMember::setBirthDate(const std::string& date) { date_of_birth = date; }
std::string FamilyMember::getBirthDate() const { return date_of_birth; }

void FamilyMember::setDeathDate(const std::string& date) { date_of_death = date; }
std::string FamilyMember::getDeathDate() const { return date_of_death; }

void FamilyMember::setAge(int age) { this->age = age; }
int FamilyMember::getAge() const { return age; }

void FamilyMember::addParent(const std::string& p) {
    // если массив ещё не создан
    if (parents_count == 0) {
        parents = new std::string[1];
        parents[0] = p;
        parents_count = 1;
        return;
    }

    // создаём новый массив на 1 больше
    std::string* tmp = new std::string[parents_count + 1];
    for (int i = 0; i < parents_count; ++i)
        tmp[i] = parents[i];
    tmp[parents_count] = p;

    delete[] parents;
    parents = tmp;
    ++parents_count;
}

std::string FamilyMember::getParents() const {
    std::string res = {};
    if (parents_count == 0) {
        return res;
    }
    for (int i = 0; i < parents_count; ++i)
        res += parents[i] + (i + 1 < parents_count ? "; " : "");
    return res;
}

void FamilyMember::addChild(const std::string& c) {
    if (children_count == 0) {
        children = new std::string[1];
        children[0] = c;
        children_count = 1;
        return;
    }

    std::string* tmp = new std::string[children_count + 1];
    for (int i = 0; i < children_count; ++i)
        tmp[i] = children[i];
    tmp[children_count] = c;

    delete[] children;
    children = tmp;
    ++children_count;
}

std::string FamilyMember::getChild() const {
    std::string res = {};
    if (children_count == 0) {
        return res;
    }
    for (int i = 0; i < children_count; ++i)
        res += children[i] + (i + 1 < children_count ? "; " : "");
    return res;
}

void FamilyMember::setSpouse(const std::string& s) { spouse = s; }
std::string FamilyMember::getSpouse() const { return spouse; }



//     // Реализация Base
//     void show() const override;
//     void edit() override;
//     void save(std::ostream& os) const override;
//     void load(std::istream& is) override;