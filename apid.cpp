#include <iostream>
#include <vector>
#include <math.h>
#include "bigint.cpp"
using namespace std;

class Apid
{
    public:
      //constructors
        Apid();
        Apid(const BigInt&);
        Apid(const BigInt&, const long int&);
        Apid(const Apid&);
    //Comparators
        bool operator>(const Apid& rhs) const;
        bool operator<(const Apid& rhs) const;
        bool operator==(const Apid& rhs) const;
        bool operator<=(const Apid& rhs) const;
        bool operator>=(const Apid& rhs) const;
        bool operator!=(const Apid& rhs) const;

        bool operator>(const long int rhs) const {return (*this>Apid(rhs));}
        bool operator<(const long int rhs) const {return (*this<Apid(rhs));}
        bool operator==(const long int rhs) const {return (*this==Apid(rhs));}
        bool operator<=(const long int rhs) const {return (*this<=Apid(rhs));}
        bool operator>=(const long int rhs) const {return (*this>=Apid(rhs));}
        bool operator!=(const long int rhs) const {return (*this!=Apid(rhs));}

    //Unary Operators
        Apid operator++();
        Apid operator--();
        Apid operator-();

    //Binary Operators
        Apid operator+(const Apid& rhs) const;
        Apid operator-(const Apid& rhs) const;
        Apid operator*(const Apid& rhs) const;
        Apid operator/(const Apid& rhs) const;
        Apid operator%(const Apid& rhs) const;
        Apid operator^(const Apid& rhs) const;

        Apid operator+(const int& rhs) const {return (*this+Apid(rhs));}
        Apid operator-(const int& rhs) const {return (*this-Apid(rhs));}
        Apid operator*(const int& rhs) const {return (*this*Apid(rhs));}
        Apid operator/(const int& rhs) const {return (*this/Apid(rhs));}
        Apid operator%(const int& rhs) const {return (*this%Apid(rhs));}
        Apid operator^(const int& rhs) const {return (*this^Apid(rhs));}
        //=
        //<<	>>  +=	-=	/=	%=	^=	*=
    private:
        BigInt number;
        long int mantis;
        friend std::ostream& operator <<(std::ostream& Stream, Apid& Obj);

};
Apid::Apid()
{
    this->number=1;
    this->mantis=0;
}
Apid::Apid(const BigInt& a)
{
    this->number=a;
    this->mantis=0;
}
Apid::Apid(const BigInt& a, const long int& b)
{
    this->number=a;
    this->mantis=b;
}
Apid::Apid(const Apid& rhs)
{
    this->number=rhs.number;
    this->mantis=rhs.mantis;
}

std::ostream& operator <<(std::ostream& Stream, Apid& Obj)
{
    Stream << Obj.number;
    Stream << "e" << Obj.mantis;
    return Stream;
}

bool Apid::operator>(const Apid& rhs) const
{
    if (this->mantis<rhs.mantis)
        return false;
    if (this->mantis>rhs.mantis)
        return true;
    return (this->number>rhs.number);
}

bool Apid::operator<(const Apid& rhs) const
{
    if (this->mantis>rhs.mantis)
        return false;
    if (this->mantis<rhs.mantis)
        return true;
    return (this->number<rhs.number);
}

bool Apid::operator==(const Apid& rhs) const
{
    if (this->mantis!=rhs.mantis)
        return false;
    return (this->number==rhs.number);
}

bool Apid::operator<=(const Apid& rhs) const
{
    return not(*this>rhs);
}

bool Apid::operator>=(const Apid& rhs) const
{
    return not(*this<rhs);
}

bool Apid::operator!=(const Apid& rhs) const
{
    return not(*this==rhs);
}


Apid Apid::operator+(const Apid& rhs) const
{
    Apid rtn;
    rtn.mantis=min(this->mantis,rhs.mantis);
    if (this->mantis>rhs.mantis)
        rtn.number=this->number*(BigInt(10)^(this->mantis-rhs.mantis))+rhs.number;
    else
        rtn.number=this->number+rhs.number*(BigInt(10)^(rhs.mantis-this->mantis));
    return rtn;
}
Apid Apid::operator-(const Apid& rhs) const
{
    Apid rtn;
    rtn.mantis=min(this->mantis,rhs.mantis);
    if (this->mantis>rhs.mantis)
        rtn.number=this->number*(BigInt(10)^(this->mantis-rhs.mantis))-rhs.number;
    else
        rtn.number=this->number-rhs.number*(BigInt(10)^(rhs.mantis-this->mantis));
    return rtn;
}
Apid Apid::operator*(const Apid& rhs) const
{
    Apid rtn;
    rtn.mantis=rhs.mantis+this->mantis;
    rtn.number=rhs.number*this->number;
    return rtn;
}
Apid Apid::operator/(const Apid& rhs) const
{
    Apid rtn;
    rtn.mantis=this->mantis-rhs.mantis;
    rtn.number=this->number/rhs.number;
    return rtn;
}

Apid Apid::operator^(const Apid& rhs) const
{
    Apid rtn(1);
    for (BigInt i = 0; i < rhs; i++) {
        rtn=rtn*rhs;
    }
    return rtn;
}

int main(int argc, char const *argv[]) {
    //Apid number1(BigInt(10),0);
    //Apid number2(BigInt(3),3);
    //Apid number3(number1/number2);
    //cout<<number1<<endl;
    //cout<<number2<<endl;
    //cout<<number3<<endl;
    return 0;
}
