#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;

int main() 
{ 
    double n;
    cin >> n;
    cout << fixed << setprecision(3) <<  (sqrt(n)-1)/2 << endl;
    return 0; 
}