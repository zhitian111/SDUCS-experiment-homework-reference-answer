#include<iostream>
using namespace std;
int main(){
    int a,b,c;
    cin >> a >> b >> c;
    bool aodd = a % 2 == 1;
    bool bodd = b % 2 == 1;
    bool codd = c % 2 == 1;

    if (aodd == true && bodd == true && codd == true){
        cout << "odd";
    }
    else if (aodd == false && bodd == false && codd == false){
        cout << "even";
    }
    else if (aodd != bodd && aodd != codd && bodd == codd){
        cout << a;
    }
    else if (aodd != bodd && aodd == codd && bodd != codd){
        cout << b;
    }
    else if (aodd == bodd && aodd != codd && bodd != codd){
        cout << c;
    }

    return 0;
}