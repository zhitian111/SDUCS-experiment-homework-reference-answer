#include<iostream>
using namespace std;
class Complex{
    private:
    double R;
    double i;
    public:
    void add(Complex b);
    Complex(int a,int b){
        R=a*1.0;
        i=b*1.0;
    }
    Complex(double a){
        R=a;i=0;
    }
    void show();
};

void Complex::add(Complex b){
    this->R+=b.R;
    this->i+=b.i;
}

void Complex::show(){
    cout<<R;
    if(i!=0){
        cout<<"+"<<i<<"i";
    }
    cout<<endl;
}
int main(){
    Complex c1(5,8);
    Complex c2=6.7;
    c1.add(c2);
    c1.show();
}