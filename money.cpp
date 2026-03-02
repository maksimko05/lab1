#include "money.h"
#include <iostream>

using namespace std;

void addMoney(Money *money, Money *addMoney){
    money->grn += addMoney->grn;
    money->cop += addMoney->cop;
}

void multiplyMoney(Money *money, int count){
    money->grn *= count;
    money->cop *= count;
}

void roundMoney(Money *money){
    money->cop = money->cop / 10 * 10 + (money->cop % 10 >= 8 ? 10 : 0);
    if(money->cop >= 100){
        int newGrn = money->cop / 100;
        money->grn += newGrn;
        money->cop %= 100;
    }
}

void printMoney(Money *money){
    std::cout << money->grn << "grn " << money->cop << "cop\n"; 
}

void calcGeneralPrice(const char *path){
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
                if(count < 0 || grn < 0 || cop < 0){
                    cout << "incorrect format of input\n";
                    fclose(file);
                    return;
                }
                Money newMoney = {grn, cop};
                multiplyMoney(&newMoney, count);
                addMoney(&money, &newMoney);
            }
            else{
                cout << "incorrect format of input\n";
                fclose(file);
                return;
            }
        }
        cout << "before round: ";
        printMoney(&money);
        roundMoney(&money);
        cout << "after round: ";
        printMoney(&money);
        fclose(file);
    }
    else{
        cout << "Error open file: " << err << endl;
        return;
    }
}