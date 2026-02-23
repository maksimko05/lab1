#include <iostream>
#include "money.h"

using namespace std;

int main(){
    FILE *file;
    int err = fopen_s(&file, "./input.txt", "r");
    
    Money money = {0, 0};
    if(err == 0 && file != nullptr){
        char buffer[256];
        int grn;
        short int cop;
        int count;
        char* product;
        while (fgets(buffer, sizeof(buffer), file)) {
            if (sscanf(buffer, "%s %u %hu %u", product, &grn, &cop, &count) == 4) {
                if(count <= 0 || grn < 0 || cop < 0 || cop >= 100){
                    cout << "incorrect format of input\n";
                    return 0;
                }
                Money newMoney = {grn, cop};
                multiplyMoney(&newMoney, count);
                addMoney(&money, &newMoney);
            }
            else{
                cout << "incorrect format of input\n";
                return 0;
            }
        }
        roundMoney(&money);
        printMoney(&money);
        fclose(file);
    }
    else{
        cout << "Error open file: " << err << endl;
        return 0;
    }
}