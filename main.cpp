// Класс Фамильное дерево хранит данные о семье.Каждый член семьи имеет :
// ФИО, знания о родителях, знания о супруге, знания о своих детях, дату
// рождения, дату смерти(если есть), возраст

#include <iostream>
#include "Base.h"
#include "FamilyMember.h"
#include "Keeper.h"

int main(){

    std::cout << "Начало лабы"<< std::endl;
    base_hello();
    family_hello();
    keeper_hello();
    
    return 0;
}
