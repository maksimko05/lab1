#include "money.h"
#include <iostream>

using namespace std;

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

void calcGeneralPrice(char *path){
    FILE *file;
    int err = fopen_s(&file, path, "r");
    
    Money money = {0, 0};
    if(err == 0 && file != nullptr){
        char buffer[256];
        int grn;
        short int cop;
        int count;
        char product[256];
        while (fgets(buffer, sizeof(buffer), file)) {
            if (sscanf(buffer, "%s %u %hu %u", product, &grn, &cop, &count) == 4) {
                if(count <= 0 || grn < 0 || cop < 0 || cop >= 100){
                    cout << "incorrect format of input\n";
                    return;
                }
                Money newMoney = {grn, cop};
                multiplyMoney(&newMoney, count);
                addMoney(&money, &newMoney);
            }
            else{
                cout << "incorrect format of input\n";
                return;
            }
        }
        roundMoney(&money);
        printMoney(&money);
        fclose(file);
    }
    else{
        cout << "Error open file: " << err << endl;
        return;
    }
}