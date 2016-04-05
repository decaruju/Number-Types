#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

vector<unsigned int> reverse(vector<unsigned int> vect)
{
  vector<unsigned int> temp;

  for (int i = 0; i < vect.size(); i++)
    temp.push_back(vect[vect.size()-i-1]);

  return temp;
}

class BigInt
{
    public:
      //constructors
        BigInt();
        BigInt(const long int&);
        BigInt(const vector<unsigned int>&, const bool);
        BigInt(const BigInt&);
        BigInt(const BigInt& ,const bool );
    //Assignement
        void operator=(const BigInt& number){this->digits = number.digits; this->isPositive = number.isPositive;}
    //Comparators
        bool operator>(const BigInt& rhs) const ;
        bool operator<(const BigInt& rhs) const ;
        bool operator==(const BigInt& rhs) const ;
        bool operator<=(const BigInt& rhs) const ;
        bool operator>=(const BigInt& rhs) const ;
        bool operator!=(const BigInt& rhs) const ;

        bool operator>(const long int rhs) const {return (*this>BigInt(rhs));}
        bool operator<(const long int rhs) const {return (*this<BigInt(rhs));}
        bool operator==(const long int rhs) const {return (*this==BigInt(rhs));}
        bool operator<=(const long int rhs) const {return (*this<=BigInt(rhs));}
        bool operator>=(const long int rhs) const {return (*this>=BigInt(rhs));}
        bool operator!=(const long int rhs) const {return (*this!=BigInt(rhs));}

    //Unary Operators
        BigInt operator++();
        BigInt operator--();
        BigInt operator-() const;
    //Binary Operators
        BigInt operator+(const BigInt& rhs) const ;
        BigInt operator-(const BigInt& rhs) const ;
        BigInt operator*(const BigInt& rhs) const ;
        BigInt operator/(const BigInt& rhs) const ;
        BigInt operator%(const BigInt& rhs) const ;
        BigInt operator^(const BigInt& rhs) const ;

        BigInt operator+(const int rhs) const {return (*this+BigInt(rhs));}
        BigInt operator-(const int rhs) const {return (*this-BigInt(rhs));}
        BigInt operator*(const int rhs) const {return (*this*BigInt(rhs));}
        BigInt operator/(const int rhs) const {return (*this/BigInt(rhs));}
        BigInt operator%(const int rhs) const {return (*this%BigInt(rhs));}
        BigInt operator^(const int rhs) const {return (*this^BigInt(rhs));}
        //=
        //<<	>>  +=	-=	/=	%=	^=	*=
    private:
        vector<unsigned int> digits;
        bool isPositive;
        friend std::ostream& operator <<(std::ostream&, const BigInt);
};

//Constructors
    BigInt::BigInt()
    {
        this->isPositive=true;
        this->digits.push_back(0);
    }

    BigInt::BigInt(const long int& a)
    {
        vector<unsigned int> return_vector;
        if (a<0)
        {
            this->isPositive=false;
            return_vector.push_back(-a);
        }
        else
        {
            this->isPositive=true;
            return_vector.push_back(a);
        }
        *this=BigInt(return_vector,a>=0);
    }

    BigInt::BigInt(const vector<unsigned int>& number, const bool a)
    {
        this->isPositive=a;
        int carry=0;

        for (int i = 0; i<number.size(); i++)
        {
            this->digits.push_back(number[i]%10000+carry);
            carry=number[i]/10000;
        }

        if (carry != 0)
            this->digits.push_back(carry);

        while (this->digits.size()>0&&this->digits.back()==0)
            this->digits.pop_back();
    }

    BigInt::BigInt(const BigInt& number)
    {
        *this=number;
    }

    BigInt::BigInt(const BigInt& number, bool isPositive)
    {
        *this=number;
        this->isPositive=isPositive;
    }
//Stream operator

std::ostream& operator <<(std::ostream& Stream, BigInt Obj)
{
    if (not(Obj.isPositive))
        Stream<<"-";
        Stream << Obj.digits.back();
        for (int i = Obj.digits.size()-2; i >= 0; i--)
        {
            if (Obj.digits[i]==0)
                Stream<<"0000";
            else
            {
                for (int j = 0; j < 4-(int)log10(Obj.digits[i])-1; j++)
                  Stream<<"0";
                Stream << Obj.digits[i];
            }
        }
    return Stream;
}

//Comparators

bool BigInt::operator>(const BigInt& rhs) const
{
    if (this->isPositive && not(rhs.isPositive))
        return true;
    else if (not(this->isPositive) && rhs.isPositive)
        return false;
    else if (not(this->isPositive) && (rhs.isPositive))
        return *this<rhs;
    if (this->digits.size()>rhs.digits.size())
       return true;
    else if (this->digits.size()<rhs.digits.size())
        return false;
    else
    {
        for (int i = 0; i < this->digits.size(); i++)
        {
            if (this->digits[i]>rhs.digits[i])
                return true;
            else if(this->digits[i]<rhs.digits[i])
                return false;
        }
        return false;
    }
}

bool BigInt::operator<(const BigInt& rhs) const
{
    if (this->isPositive < rhs.isPositive)
        return true;
    else if (this->isPositive > rhs.isPositive)
        return false;
    if (this->digits.size()<rhs.digits.size())
        return true;
    else if (this->digits.size()>rhs.digits.size())
        return false;
    else
    {
        for (int i = 0; i < this->digits.size(); i++)
        {
            if (this->digits[i]<rhs.digits[i])
                return true;
            else if(this->digits[i]>rhs.digits[i])
                return false;
        }
        return false;
    }
}

bool BigInt::operator==(const BigInt& rhs) const
{
    if (this->isPositive != rhs.isPositive)
        return false;
    if (this->digits.size()!=rhs.digits.size())
        return false;
    else
    {
        for (int i = 0; i < this->digits.size(); i++)
        {
            if (this->digits[i]!=rhs.digits[i])
                return false;
        }
        return true;
    }
}

bool BigInt::operator<=(const BigInt& rhs) const
{
    return not(*this>rhs);
}

bool BigInt::operator>=(const BigInt& rhs) const
{
    return not(*this<rhs);
}

bool BigInt::operator!=(const BigInt& rhs) const
{
    return not(*this==rhs);
}

//Unary Operators

BigInt BigInt::operator++()
{
    if (this->isPositive)
        (this->digits[0])++;
    else if (*this<-1)
        (this->digits[0])--;
    else
        *this=BigInt(0);
}

BigInt BigInt::operator--()
{
    if (not(this->isPositive))
        (this->digits[0])--;
    else if (*this>1)
        (this->digits[0])++;
    else
        *this=BigInt(0);
}

BigInt BigInt::operator-() const
{
    return (BigInt(*this,not(this->isPositive)));
}

//Binary Operators

BigInt BigInt::operator+(const BigInt& rhs) const
{
    if (not(this->isPositive) && not(rhs.isPositive))
        return BigInt((-*this)+(-rhs),false);
    else if (not(this->isPositive))
        return rhs-*this;
    else if (not(rhs.isPositive))
        return *this-BigInt(rhs,true);

    vector<unsigned int> return_digits;

    for (int i = 0; i < min(this->digits.size(),rhs.digits.size()); i++)
    {
        return_digits.push_back(this->digits[i]+rhs.digits[i]);
    }

    if (this->digits.size()>rhs.digits.size())
    {
        for (int i = rhs.digits.size(); i < this->digits.size(); i++)
            return_digits.push_back(this->digits[i]);
    }
    else if (this->digits.size()<rhs.digits.size())
    {
        for (int i = this->digits.size(); i < rhs.digits.size(); i++)
            return_digits.push_back(rhs.digits[i]);
    }
    return (BigInt(return_digits,true));
}

BigInt BigInt::operator-(const BigInt& rhs) const
{
    vector<unsigned int> return_vector;
    bool carry(0);

    if (*this<rhs)
        return BigInt(rhs-*this,false);

    for (int i = 0; i < rhs.digits.size(); i++) {
        if (this->digits[i]<carry+rhs.digits[i])
        {
            return_vector.push_back(10000+this->digits[i]-rhs.digits[i]-carry);
            carry=1;
        }
        else
        {
            return_vector.push_back(this->digits[i]-rhs.digits[i]-carry);
            carry=0;
        }
    }
    for (int i = rhs.digits.size(); i < this->digits.size(); i++) {
        if (this->digits[i]<carry)
        {
            return_vector.push_back(10000-carry);
            carry=1;
        }
        else
        {
            return_vector.push_back(this->digits[i]-carry);
            carry=0;
            cout<<"pipi"<<endl;
        }
    }
    for (int i = 0; i < return_vector.size(); i++) {
        cout<<return_vector[i]<<endl;
    }
    return BigInt(return_vector,true);
}

BigInt BigInt::operator*(const BigInt& rhs) const
{
    vector<unsigned int> rtn( rhs.digits.size()*this->digits.size(),0 );

    for (int i = 0; i < rhs.digits.size(); i++) {
      for (int j = 0; j < this->digits.size(); j++) {
        rtn[i+j]+=(rhs.digits[i])*(this->digits[j]);
      }
    }

    if ((rhs.isPositive && this->isPositive)|| (not(rhs.isPositive) && not(this->isPositive) ) ) {
      return BigInt(rtn,true);
    }
    return BigInt(rtn,false);
}

BigInt BigInt::operator/(const BigInt& rhs) const
{
    BigInt rtn;
    BigInt i;
    while (*this>rtn)
    {
        rtn=rtn+rhs;
        ++i;
    }
    return i;
}
BigInt BigInt::operator%(const BigInt& rhs) const
{
    BigInt rtn=0;
    BigInt i=0;
    while (*this>rtn)
    {
        rtn=rtn+rhs;
        ++i;
    }
    return (*this-rtn*rhs);
}
BigInt BigInt::operator^(const BigInt& rhs) const
{
    BigInt rtn(1);
    for (BigInt i(0); i < rhs; i=i+1)
        rtn=rtn**this;
    return rtn;
}

int main()
{
        BigInt n(vector<unsigned int>({0,0,1}),true);
        BigInt m(1);
        BigInt o(n-m);
        cout<<o<<endl;
        cout<<n<<endl;

    return 0;
}
