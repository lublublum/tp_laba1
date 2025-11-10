#ifndef BASE_H
#define BASE_H

#include <iostream>
#include <string>

void base_hello();

class Base
{
public:
    virtual void show() const = 0;
    virtual void edit() = 0;
    virtual void save(std::ostream& os) const = 0;
    virtual void load(std::istream& is) = 0;
    virtual const char* getType() const = 0;
    Base(){
        std::cout << "\033[33mBase constructor called\033[0m\n";
    }
    virtual ~Base() {
        std::cout << "\033[33mBase destructor called\033[0m\n";
    }
};

#endif //BASE_H