// currency class using three data members
// (sign, dollars, and cents) to
// represent an instance/object

#ifndef currency_
#define currency_

#include <iostream>


using namespace std;

enum signType {plus, minus};

class currency 
{
   public:
      // constructor
      currency(signType theSign = signType::plus,
               unsigned long theDollars = 0,
               unsigned int theCents = 0);
      // destructor
      ~currency() {}
      void setValue(signType, unsigned long, unsigned int);
      void setValue(double);
      signType getSign() const {return sign;}
      unsigned long getDollars() const {return dollars;}
      unsigned int getCents() const {return cents;}
      currency add(const currency&) const;
      currency& increment(const currency&);
      
      void output() const;
      //作业部分
      void input();
      currency subtract(const currency& x);
      currency percent(const double &x);
      currency mutiply(const double &x);
      currency divide(const double &x);
   private:
      signType sign;           // sign of object
      unsigned long dollars;   // number of dollars
      unsigned int cents;      // number of cents

};

currency::currency(signType theSign, unsigned long theDollars,
                                     unsigned int theCents)
{// Create a currency object.
   setValue(theSign, theDollars, theCents);
}

void currency::setValue(signType theSign, unsigned long theDollars,
                                          unsigned int theCents)
{// Set currency value.

   sign = theSign;
   dollars = theDollars;
   cents = theCents;
}
   
void currency::setValue(double theAmount)
{// Set currency value.
   if (theAmount < 0) {sign = signType::minus;
                       theAmount = -theAmount;}
   else sign = signType::plus;

   dollars = (unsigned long) theAmount;
             // extract integer part
   cents = (unsigned int) ((theAmount + 0.001 - dollars) * 100);
             // get two decimal digits
}

currency currency::add(const currency& x) const
{// Add x and *this.
   long a1, a2, a3;
   currency result;
   // convert invoking object to signed integers
   a1 = dollars * 100 + cents;
   if (sign == signType::minus) a1 = -a1;
   
   // convert x to signed integer
   a2 = x.dollars * 100 + x.cents;
   if (x.sign == signType::minus) a2 = -a2;
   
   a3 = a1 + a2;
    
   // convert to currency representation
   if (a3 < 0) {result.sign = signType::minus; a3 = -a3;}
   else result.sign = signType::plus;
   result.dollars = a3 / 100;
   result.cents = a3 - result.dollars * 100;
   
   return result;
}

currency& currency::increment(const currency& x)
{// Increment by x.
   *this = add(x);
   return *this;
}

void currency::output() const
{// Output currency value.
   if (sign == signType::minus) cout << '-';
   cout << '$' << dollars << '.';
   if (cents < 10) cout << '0';
   cout << cents;
}

//作业部分
void currency::input()
{
    unsigned long theDollars;
    unsigned int theCents;
    cin >> theDollars >> theCents;
    this->dollars = theDollars;
    this->cents = theCents;
}


currency currency::subtract(const currency &x)
{
    if (this->cents<x.getCents())
    {
        this->cents += 100;
        if (dollars > 0&&sign == signType::plus)
        {
            this->dollars -= 1;
        }
        if (dollars > 0 && sign == signType::minus)
        {
            this->dollars += 1;
        }
    }
    this->dollars = this->dollars - x.getDollars();
    this->cents = this->cents - x.getCents();
    currency result(sign, dollars, cents);
    return result;
}

currency currency::percent(const double& x)
{
    double tem = x / 100;
    unsigned long theDollars;
    unsigned int theCents;
    theDollars = this->dollars * tem;
    theCents = this->cents * tem + (dollars * tem - int(dollars * tem));
    currency result(sign, dollars, cents);
    return result;
}

currency currency::mutiply(const double& x)
{
    double tem = x ;
    unsigned long theDollars;
    unsigned int theCents;
    theDollars = this->dollars * tem;
    theCents = this->cents * tem + (dollars * tem - int(dollars * tem));
    currency result(sign, dollars, cents);
    return result;
}

currency currency::divide(const double& x)
{
    return(mutiply(1 / x));
}


#endif

