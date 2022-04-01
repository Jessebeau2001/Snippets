#include "rational.h"

#include <iostream>
#include <sstream>
#include <cmath>        // for inf and NaN checks
#include <algorithm>        

using std::cout;
using std::endl;
using std::stoi;
using std::stringstream;

/**
 * Base constructor for Rational
 * @param num Numerator.
 * @param den Denominator.
 */
Rational::Rational(int num, int den)
{
    num_ = num;
    den_ = den;
    compile();
}

/**
 * @brief Construct a new Rational object. Initiales denominator with 1.
 * @param num Numerator.
 */
Rational::Rational(int num) : Rational(num, 1) {}

/**
 * Construct a new Rational object with all values initialized as 1.
 */
Rational::Rational() : Rational(1, 1) {}

/**
 * Construct a new Rational object.
 * @param expr Expression in form: "p/q".
 * @throws No error but defaults to (1/1) if string expression is incorrect
 */
Rational::Rational(string expr)
{
    auto pos = expr.find("/");
    int p, q;
    try {
        p = std::stoi(expr.substr(0, pos));
    } catch(std::exception e) {
        cout << "Error in numerator of expression '" << expr << "', defaulting to 1." <<endl;
        p = 1;
    }

    try {
        q = std::stoi(expr.substr(pos + 1));
    } catch (std::exception e) {
        cout << "Error in denominator of expression '" << expr << "', defaulting to 1." <<endl;
        q = 1;
    }
    *this = Rational(p, q);
}

/**
 * Performs calculation based on inputted string expression. Example:
 * "4/5 - 9/-4" will return Rational{61, 20}
 * @param expr String representation of expression.
 * @return Result of expression.
 */
Rational Rational::calculate(string expr)
{
    // cout << "Full expression: " << expr << "\n";
    stringstream oss{expr};
    string a, b;
    char op;

    oss >> a >> op >> b;
    // cout << "a: " << a << ", b: " << b << ", operation: " << op << ".\n";

    if(a == "sqrt") return Rational{op + b}.sqrt();     // 'op + b' because the operator holds the first number, bit cheesy but works
    
    switch (op) {
        case '+':
            return Rational{a} + Rational{b};
        case '-':
            return Rational{a} - Rational{b};
        case '*':
            return Rational{a} * Rational{b};
        case '/':
            return Rational{a} / Rational{b};
        case '^':
            return Rational{a}.pow(std::stoi(b));
    }


    return Rational{};
}


/**
 * Calculates greatest common divider using std::__gcd() from <algorithm>. Always returns absolute value of gcd.
 * @return Abs of gcd.
 */
int Rational::get_gcd()
{
    return std::abs(std::__gcd(num_, den_));
}

/**
 * Returns constructed string based on Rational values.
 * @return String representation of rational.
 */
string Rational::to_string()
{
    stringstream oss;
    oss << "(" << num_ << "/" << den_ << ")";
    return oss.str();
}

/**
 * Returns worked out Rational in decimal form.
 * @return Decimal form of Rational.
 */
double Rational::to_double()
{
    return decimal_;
}

/**
 * Checks whether Rational is positive.
 * @return true when positive.
 */
bool Rational::is_positive()
{
    return (decimal_ > 0);
}

/**
 * Checks whether Rational is infinite.
 * @return true when infinite.
 */
bool Rational::is_inf()
{
    return std::isinf(decimal_);
}

/**
 * Checks whether Rational is NaN (Not a Number).
 * @return true when not a number.
 */
bool Rational::is_nan()
{
    return std::isnan(decimal_);
}

/**
 * Compiles all internal values based on existing numerator and demoninator.
 * This should always be called when either value has been subject to change.
 */
void Rational::compile()
{
    if (den_ < 0) flip_sign();
    try_simplify();
    decimal_ = (double) num_ / den_;
}

/**
 * Flips the sign of both the numerator and denominator.
 */
void Rational::flip_sign()
{
    num_ *= -1;
    den_ *= -1;
}

/**
 * Simplifies both the numerator and denominator when possible.
 */
void Rational::try_simplify()
{
    auto gcd = get_gcd();
    if (gcd == 0) return;
    num_ /= gcd;
    den_ /= gcd;
}