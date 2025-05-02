#include "Fraction.hpp"
#include <iostream>
#include <algorithm>

using namespace std;
/**
 * Default constructor for Fraction class.
 * @param numerator Numerator of the fraction (defaults to 0).
 * @param denominator Denominator of the fraction (defaults to 1). Cannot be 0.
 */
Fraction::Fraction(int numerator = 0, int denominator = 1){
    NUMER = numerator;
    if(denominator == 0){
        cerr << "Denominator cannot be 0, setting denom by default to 1..." << endl;
        DENOM = 1;
    } else {
        DENOM = denominator;
    }
}

/**
 * Copy constructor for Fraction.
 *
 * @param[in] f The Fraction object to be copied.
 */
Fraction::Fraction(const Fraction &f)
{
    NUMER = f.NUMER;
    DENOM = f.DENOM;
}

int Fraction::getNUMER()
{
    return NUMER;
}

int Fraction::getDENOM()
{
    return DENOM;
}

/**
 * Simplifies the fraction by dividing the numerator and denominator
 * by their greatest common divisor (GCD) and returns the simplified
 * fraction.
 *
 * @return A new Fraction object representing the simplified fraction.
 */

Fraction Fraction::simplify()
{
    return Fraction(NUMER/__gcd(NUMER,DENOM), DENOM/__gcd(NUMER,DENOM));
}


/**
 * Overload of the addition operator for Fraction objects.
 *
 * @param[in] Tobeadded The Fraction object to be added to this object.
 * @return A new Fraction object representing the sum of the two input
 *         fractions.
 * 
 * The function first calculates the greatest common divisor (GCD) of the
 * denominators of the two fractions. Then it calculates the least common
 * multiple (LCM) of the two denominators. The numerator of the result is
 * calculated by multiplying the numerators of the two fractions by the
 * coefficients needed to scale them to the LCM, and then adding the two
 * scaled numerators. The result is returned as a new Fraction object.
 */
Fraction Fraction::operator+(const Fraction& Tobeadded) const
{   
    int gcd = __gcd(this->DENOM, Tobeadded.DENOM);
    int newDenom = (this->DENOM*Tobeadded.DENOM)/gcd;
    int temp1 = newDenom/this->DENOM;
    int temp2 = newDenom/Tobeadded.DENOM;
    int newNumer = this->NUMER * temp1 + Tobeadded.NUMER * temp2;
    return Fraction(newNumer, newDenom);
}
/**
 * Subtracts another fraction from this one and returns the result.
 *
 * @param[in] Tobesubed The Fraction object to be subtracted.
 *
 * @return A new Fraction object representing the result of the subtraction.
 */

Fraction Fraction::operator-(const Fraction& Tobesubed) const
{
    int gcd = __gcd(this->DENOM, Tobesubed.DENOM);
    int newDenom = this->DENOM*Tobesubed.DENOM/gcd;
    int temp1 = newDenom/this->DENOM;
    int temp2 = newDenom/Tobesubed.DENOM;
    int newNumer = this->NUMER * temp1 - Tobesubed.NUMER *temp2;
    return Fraction(newNumer, newDenom);
}

Fraction Fraction::operator*(const Fraction& Tobemuled) const
{
    return Fraction(this->NUMER*Tobemuled.NUMER, this->DENOM*Tobemuled.DENOM);
}

Fraction Fraction::operator/(const Fraction& Tobedived) const
{
    Fraction UpsideDown(Tobedived.DENOM,Tobedived.NUMER);
    return *this * UpsideDown;
}

bool Fraction::operator<(const Fraction &SomethingGT) const
{
    return (*this - SomethingGT).NUMER<0;
}

bool Fraction::operator<=(const Fraction &SomethingGEQ) const
{
    return (*this - SomethingGEQ).NUMER<=0;
}

bool Fraction::operator==(const Fraction &SomethingEQ) const
{
    return (*this - SomethingEQ).NUMER==0;
}

bool Fraction::operator!=(const Fraction &SomethingNEQ) const
{
    return (*this - SomethingNEQ).NUMER!=0;
}

bool Fraction::operator>=(const Fraction &SomethingLEQ) const
{
    return (*this - SomethingLEQ).NUMER>=0;
}

bool Fraction::operator>(const Fraction &SomethingLT) const
{
    return (*this - SomethingLT).NUMER>0;
}

Fraction::operator double() const
{
    return NUMER/(double)DENOM;
}

Fraction::operator string() const
{
    return to_string(NUMER) + "/" + to_string(DENOM);
}

void Fraction::testPrint()
{
    cout << NUMER << "/" << DENOM << endl;
}

Fraction::~Fraction()
{
}

istream & operator >>(istream & is, Fraction & obj)
{
    char slash;
    is >> obj.NUMER >> slash >> obj.DENOM;
    return is;
}

ostream &operator <<(ostream &os, const Fraction &f)
{
    os << f.NUMER << "/" << f.DENOM;
    return os;
}

/**
 * @brief Construct a Fraction object from a string representation of a
 *        fraction.
 *
 * @param[in] str The string representation of the fraction.
 *
 * @return A new Fraction object representing the fraction.
 *
 * The function first checks if the input string is empty. If it is, it
 * returns an empty Fraction object. Otherwise, it splits the string into
 * two parts using the '/' character as the delimiter and constructs a new
 * Fraction object with the two parts. If the second part is zero, it throws
 * an invalid_argument exception.
 */
Fraction fromString(const std::string &str)
{
    if (str.empty())
    {
        throw invalid_argument("No str detected!");
    }
    size_t pos = str.find('/');
    if (pos == std::string::npos)
    {
        throw std::invalid_argument("Invalid fraction string: " + str);
    }
    int numer = std::stoi(str.substr(0, pos));
    int denom = std::stoi(str.substr(pos + 1));
    if (denom == 0)
    {
        throw std::invalid_argument("Denominator cannot be zero");
    }
    return Fraction(numer, denom);
}
