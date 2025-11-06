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
    virtual ~Base();
};

#endif //BASE_H