#include "FamilyMember.h"

void family_hello() {
    std::cout << "Family hello!\n";
}

// ==================== Конструкторы и оператор ====================

FamilyMember::FamilyMember()
    : full_name(""), date_of_birth(""), date_of_death(""), age(0),
    father(nullptr), mother(nullptr), spouse(nullptr),
    children(nullptr), childrenCount(0), childrenCapacity(2)
{
    children = new FamilyMember * [childrenCapacity];
    for (int i = 0; i < childrenCapacity; ++i)
        children[i] = nullptr;
    std::cout << "\033[33mFamilyMember default constructor called\033[0m\n";
}

FamilyMember::FamilyMember(const std::string& name, const std::string& birth,
    const std::string& death, int age)
    : full_name(name), date_of_birth(birth), date_of_death(death), age(age),
    father(nullptr), mother(nullptr), spouse(nullptr),
    children(nullptr), childrenCount(0), childrenCapacity(2)
{
    children = new FamilyMember * [childrenCapacity];
    for (int i = 0; i < childrenCapacity; ++i)
        children[i] = nullptr;
    std::cout << "\033[33mFamilyMember constructor called for " << full_name << "\033[0m\n";
}

FamilyMember::FamilyMember(const FamilyMember& other)
    : full_name(other.full_name), date_of_birth(other.date_of_birth),
    date_of_death(other.date_of_death), age(other.age),
    father(other.father), mother(other.mother), spouse(other.spouse),
    childrenCount(other.childrenCount), childrenCapacity(other.childrenCapacity)
{
    children = new FamilyMember * [childrenCapacity];
    for (int i = 0; i < childrenCount; ++i)
        children[i] = other.children[i];
    std::cout << "\033[33mFamilyMember copy constructor called for " << full_name << "\033[0m\n";
}

FamilyMember& FamilyMember::operator=(const FamilyMember& other) {
    if (this == &other) return *this;

    delete[] children;
    full_name = other.full_name;
    date_of_birth = other.date_of_birth;
    date_of_death = other.date_of_death;
    age = other.age;

    father = other.father;
    mother = other.mother;
    spouse = other.spouse;

    childrenCapacity = other.childrenCapacity;
    childrenCount = other.childrenCount;
    children = new FamilyMember * [childrenCapacity];
    for (int i = 0; i < childrenCount; ++i)
        children[i] = other.children[i];

    std::cout << "\033[33mFamilyMember assignment operator called for " << full_name << "\033[0m\n";
    return *this;
}

FamilyMember::~FamilyMember() {
    delete[] children;
    std::cout << "\033[33mFamilyMember destructor called for " << full_name << "\033[0m\n";
}

// ==================== SET / GET ====================

void FamilyMember::setName(const std::string& name) { full_name = name; }
std::string FamilyMember::getName() const { return full_name; }

void FamilyMember::setBirthDate(const std::string& date) { date_of_birth = date; }
std::string FamilyMember::getBirthDate() const { return date_of_birth; }

void FamilyMember::setDeathDate(const std::string& date) { date_of_death = date; }
std::string FamilyMember::getDeathDate() const { return date_of_death; }

void FamilyMember::setAge(int age) { this->age = age; }
int FamilyMember::getAge() const { return age; }

// ==================== СВЯЗИ МЕЖДУ ОБЪЕКТАМИ ====================

void FamilyMember::setFather(FamilyMember* f, bool updateReverse) {
    if (f == this) return;
    father = f;
    if (updateReverse && f) f->addChild(this, false);
}

void FamilyMember::setMother(FamilyMember* m, bool updateReverse) {
    if (m == this) return;
    mother = m;
    if (updateReverse && m) m->addChild(this, false);
}

void FamilyMember::setSpouse(FamilyMember* s, bool updateReverse) {
    if (s == this) return;
    spouse = s;
    if (updateReverse && s && s->spouse != this)
        s->setSpouse(this, false);
}

void FamilyMember::addChild(FamilyMember* c, bool updateReverse) {
    if (!c || c == this) return;
    if (childrenCount >= childrenCapacity) {
        int newCap = childrenCapacity * 2;
        FamilyMember** tmp = new FamilyMember * [newCap];
        for (int i = 0; i < childrenCount; ++i)
            tmp[i] = children[i];
        for (int i = childrenCount; i < newCap; ++i)
            tmp[i] = nullptr;
        delete[] children;
        children = tmp;
        childrenCapacity = newCap;
    }
    children[childrenCount++] = c;
    if (updateReverse) {
        if (!c->father) c->setFather(this, false);
        else if (!c->mother) c->setMother(this, false);
    }
}

void FamilyMember::removeChild(FamilyMember* c, bool updateReverse) {
    if (!c) return;
    for (int i = 0; i < childrenCount; ++i) {
        if (children[i] == c) {
            for (int j = i; j < childrenCount - 1; ++j)
                children[j] = children[j + 1];
            children[--childrenCount] = nullptr;
            break;
        }
    }
    if (updateReverse) {
        if (c->father == this) c->father = nullptr;
        if (c->mother == this) c->mother = nullptr;
    }
}

void FamilyMember::clearRelationships() {
    if (father) father->removeChild(this, false);
    if (mother) mother->removeChild(this, false);
    if (spouse) spouse->spouse = nullptr;
    for (int i = 0; i < childrenCount; ++i) {
        if (children[i]) {
            if (children[i]->father == this) children[i]->father = nullptr;
            if (children[i]->mother == this) children[i]->mother = nullptr;
        }
    }
    father = nullptr;
    mother = nullptr;
    spouse = nullptr;
    childrenCount = 0;
}

void FamilyMember::showRelations() const {
    std::cout << "\n--- Family relations of " << full_name << " ---\n";
    std::cout << "Отец: " << (father ? father->full_name : "Unknown") << "\n";
    std::cout << "Мать: " << (mother ? mother->full_name : "Unknown") << "\n";
    std::cout << "Супруг/а: " << (spouse ? spouse->full_name : "None") << "\n";
    std::cout << "Дети (" << childrenCount << "): ";
    if (childrenCount == 0) std::cout << "None";
    else {
        for (int i = 0; i < childrenCount; ++i) {
            std::cout << children[i]->full_name;
            if (i < childrenCount - 1) std::cout << ", ";
        }
    }
    std::cout << "\n";
}

// ==================== ВИРТУАЛЬНЫЕ МЕТОДЫ ====================

void FamilyMember::show() const {
    std::cout << "\n=== Family Member ===\n";
    std::cout << "ФИО: " << full_name << "\n";
    std::cout << "Дата рождения: " << date_of_birth << "\n";
    std::cout << "Дата смерти: " << date_of_death << "\n";
    std::cout << "Возраст: " << age << "\n";
    showRelations();
}

void FamilyMember::edit() {
    std::cout << "Editing member " << full_name << "...\n";
    std::string tmp;
    std::cout << "Новое ФИО (Enter to skip): ";
    std::getline(std::cin, tmp);
    if (!tmp.empty()) full_name = tmp;
}

void FamilyMember::save(std::ostream& os) const {
    os << full_name << "\n"
        << date_of_birth << "\n"
        << date_of_death << "\n"
        << age << "\n";
}

void FamilyMember::load(std::istream& is) {
    std::getline(is, full_name);
    std::getline(is, date_of_birth);
    std::getline(is, date_of_death);
    is >> age;
    is.ignore();
}
