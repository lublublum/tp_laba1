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
    std::cout << "\033[33mFamilyMember constructor called for " << full_name << "\033[0m\n";
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
    std::cout << "\033[33mFamilyMember copy constructor called for " << full_name << "\033[0m\n";
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

    std::cout << "\033[33mFamilyMember assignment operator called for " << full_name << "\033[0m\n";
    return *this;
}
FamilyMember::~FamilyMember() {
    delete[] parents;
    delete[] children;
    std::cout << "\033[33mFamilyMember destructor called for " << full_name << "\033[0m\n";
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



// Реализация Base
void FamilyMember::show() const {
    std::cout << "=== FamilyMember ===\n";
    std::cout << "ФИО: " << full_name << "\n";
    std::cout << "Дата рождения: " << date_of_birth << "\n";
    std::cout << "Дата смерти: " << date_of_death << "\n";
    std::cout << "Возраст: " << age << "\n";
    std::cout << "Супруг/а: " << (spouse.empty() ? "-" : spouse) << "\n";
    std::cout << "Родители (" << parents_count << "): ";
    for (int i = 0; i < parents_count; ++i) {
        std::cout << parents[i];
        if (i + 1 < parents_count) std::cout << ", ";
    }
    std::cout << "\n";
    std::cout << "Дети (" << children_count << "): ";
    for (int i = 0; i < children_count; ++i) {
        std::cout << children[i];
        if (i + 1 < children_count) std::cout << ", ";
    }
    std::cout << "\n";

}
void FamilyMember::edit() {
    std::cout << "Editing member " << full_name << "\n";
    std::cin.ignore();
    std::string tmp;
    std::cout << "Введите ФИО (enter to skip): ";
    std::getline(std::cin, tmp);
    if (!tmp.empty()) {
        full_name = tmp;
    }
    std::cout << "Введите дату рождения (enter to skip): ";
    std::getline(std::cin, tmp);
    if (!tmp.empty()) {
        date_of_birth = tmp;
    }
    std::cout << "Введите дату смерти (enter to skip): ";
    std::getline(std::cin, tmp);
    if (!tmp.empty()) {
        date_of_death = tmp;
    }
    std::cout << "Введите возраст (0 to skip): ";
    int a; std::cin >> a;
    if (a > 0) {
        age = a;
    }
}
void FamilyMember::save(std::ostream& os) const {
    os  << full_name << "\n"
        << date_of_birth << "\n"
        << date_of_death << "\n"
        << age << "\n"
        << spouse << "\n"
        << parents_count << "\n";
    for (int i = 0; i < parents_count; ++i) os << parents[i] << "\n";
    os << children_count << "\n";
    for (int i = 0; i < children_count; ++i) os << children[i] << "\n";

}
void FamilyMember::load(std::istream& is) {
    std::string line;
    std::getline(is, full_name);
    std::getline(is, date_of_birth);
    std::getline(is, date_of_death);
    std::getline(is, line); age = std::stoi(line);
    std::getline(is, spouse);
    std::getline(is, line); // parents_count
    int pcount = std::stoi(line);
    // clear old parents
    delete[] parents; 
    parents = nullptr; 
    parents_count = 0;
    for (int i = 0; i < pcount; ++i) {
        std::getline(is, line);
        addParent(line);
    }
    std::getline(is, line);
    int ccount = std::stoi(line);
    delete[] children; 
    children = nullptr; 
    children_count = 0; 
    for (int i = 0; i < ccount; ++i) {
        std::getline(is, line);
        addChild(line);
    }

}