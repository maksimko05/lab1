#include "money.h"
#include <iostream>

void fixCops(Money *money){
    int newGrn = money->cop / 100;
    money->grn += newGrn;
    money->cop %= 100;
}

void addMoney(Money *money, Money *addMoney){
    money->grn += addMoney->grn;
    money->cop += addMoney->cop;
    fixCops(money);
}

void multiplyMoney(Money *money, int count){
    money->grn *= count;
    money->cop *= count;
    fixCops(money);
}

void roundMoney(Money *money){
    money->cop = money->cop / 10 * 10;
}

void printMoney(Money *money){
    std::cout << money->grn << "grn " << money->cop << "cop\n"; 
}