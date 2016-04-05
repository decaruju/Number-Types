#include <iostream>
#include <vector>
#include <math.h>
#include "bigint.cpp"
using namespace std;

class Rational
{
    public:
      //constructors
        Rational();
        Rational(const BigInt&);
        Rational(const BigInt&, const BigInt&);
        Rational(const Rational&);
    //Comparators
        bool operator>(const Rational& rhs) const{return(this->num*rhs.den>this->den*rhs.num);}
        bool operator<(const Rational& rhs) const{return(this->num*rhs.den<this->den*rhs.num);}
        bool operator==(const Rational& rhs) const{return(this->num*rhs.den==this->den*rhs.num);}
        bool operator<=(const Rational& rhs) const{return(this->num*rhs.den<=this->den*rhs.num);}
        bool operator>=(const Rational& rhs) const{return(this->num*rhs.den>=this->den*rhs.num);}
        bool operator!=(const Rational& rhs) const{return(this->num*rhs.den!=this->den*rhs.num);}

        bool operator>(const long int rhs) const {return (*this>Rational(rhs));}
        bool operator<(const long int rhs) const {return (*this<Rational(rhs));}
        bool operator==(const long int rhs) const {return (*this==Rational(rhs));}
        bool operator<=(const long int rhs) const {return (*this<=Rational(rhs));}
        bool operator>=(const long int rhs) const {return (*this>=Rational(rhs));}
        bool operator!=(const long int rhs) const {return (*this!=Rational(rhs));}

    //Unary Operators
        Rational operator++(){this->num=this->num+this->den;}
        Rational operator--(){this->num=this->num-this->den;}
        Rational operator-() const {return Rational(-this->num,this->den);}

    //Binary Operators
        Rational operator+(const Rational& rhs) const;
        Rational operator-(const Rational& rhs) const;
        Rational operator*(const Rational& rhs) const;
        Rational operator/(const Rational& rhs) const;
        Rational operator%(const Rational& rhs) const;
        Rational operator^(const Rational& rhs) const;

        Rational operator+(const int& rhs) const {return (*this+Rational(rhs));}
        Rational operator-(const int& rhs) const {return (*this-Rational(rhs));}
        Rational operator*(const int& rhs) const {return (*this*Rational(rhs));}
        Rational operator/(const int& rhs) const {return (*this/Rational(rhs));}
        Rational operator%(const int& rhs) const {return (*this%Rational(rhs));}
        Rational operator^(const int& rhs) const {return (*this^Rational(rhs));}
        //=
        //<<	>>  +=	-=	/=	%=	^=	*=
    private:
        BigInt num;
        BigInt den;
        friend std::ostream& operator <<(std::ostream& Stream, Rational& Obj);
        friend void reduce(Rational& obj);

};
Rational::Rational()
{
    this->den=1;
    this->num=0;
}
Rational::Rational(const BigInt& a)
{
    this->den=1;
    this->num=a;
}
Rational::Rational(const BigInt& a, const BigInt& b)
{
    this->num=a;
    this->den=b;
    if (BigInt(b)<0) {
        this->num=-BigInt(a);
        this->den=-BigInt(b);
    }
}
Rational::Rational(const Rational& rhs)
{
    this->num=rhs.num;
    this->den=rhs.den;
}

std::ostream& operator <<(std::ostream& Stream, Rational& Obj)
{
    if (Obj.num<0)
        Stream<<"-";
    Stream << Obj.num;
    Stream << "/";
    Stream << Obj.den;
    return Stream;
}


int main(int argc, char const *argv[]) {
    Rational number(BigInt(1245),BigInt(1246));
    cout<<number<<endl;
    return 0;
}
