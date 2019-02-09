#include <iostream>
#include <bitset>
using namespace std;
unsigned Cycle_find(short int c,short int generator ){
    const short int image = c;
    bool flag = false;
    unsigned cycle = 0;
    for (; ;){
        ++cycle;
        cout << bitset<8> (c) << endl;
        if(c & 1)
            flag = true;
        else
            flag = false;
        c >>= 1;
        if(flag)
            c ^= generator;
        if (c == image)
            break;
    }    
    return cycle;
}

int main(){
    short int c, cycle;
    cin >> c >> cycle;
    cout << Cycle_find(c, cycle);
    return 0;
}
