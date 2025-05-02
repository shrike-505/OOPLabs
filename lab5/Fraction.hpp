#ifndef FRACTION_HPP
#define FRACTION_HPP
#include <iostream>

class Fraction
{
private:
    int NUMER;
    int DENOM;
public:

    // ctors
    Fraction() = default;
    Fraction(int numerator, int denominator);
    Fraction(const Fraction& f);
    int getNUMER();
    int getDENOM();

    Fraction simplify();

    // Arithmetic ops
    Fraction operator+ (const Fraction& Tobeadded) const;
    Fraction operator- (const Fraction& Tobesubed) const;
    Fraction operator* (const Fraction& Tobemuled) const;
    Fraction operator/ (const Fraction& Tobedived) const;

    // Relational ops
    bool operator< (const Fraction& SomethingGT) const;
    bool operator<= (const Fraction& SomethingGEQ) const;
    bool operator== (const Fraction& SomethingEQ) const;
    bool operator!= (const Fraction& SomethingNEQ) const;
    bool operator>= (const Fraction& SomethingLEQ) const;
    bool operator> (const Fraction& SomethingLT) const;

    // typecasts
    operator double() const;
    operator std::string() const;
    
    // stream ops
    friend std::istream& operator>>(std::istream& is, Fraction& f);
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f);
    
    // Test Func
    void testPrint();
    ~Fraction();
};
Fraction fromString(const std::string& str);
#endif