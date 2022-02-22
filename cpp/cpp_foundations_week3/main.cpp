/*
    Week 3 assignment C++ foundations
    By Jesse Visscher, 477437, ETI1v.B'

    Rationals: https://en.wikipedia.org/wiki/Rational_number
    
    > About Get() Set():
    I usually write in the form of: thisIsAVar & ThisIsAFunc() nut I try im_a_func() today.
    I also feel super conflicted on the whole get() set() thing, I saw people talk about how they're
    a little bit evil, somewhat evil or even super evil but also saw some people say they're good practice.
    In a sense I do have to to agree that they can sometimes bloat the code so one could argue that a field isn't
    changed when getting or setting data it could just be public. But then again what do I know...
    I also saw an example of someone making the public version an inline variable:
        | const int & num() const { return _num; }
    But in this example they put '_' before their private members which can be seen ass 'incorrect' again,
    idk I have always done this in C# but once again saw people argue that saying int _den is bad behaviour.

    In conclusion: IDK!!, I'm just gonna go with private members end in '_' this is what I have done in previous cpp
    work & Google??? recommends it: https://google.github.io/styleguide/cppguide.html#General_Naming_Rules

*/

#include <iostream>
#include <string>
#include "rational.h"

using std::cout;
using std::string;
using std::endl;

string b_str (bool b)
{
    return b ? "True" : "False";
}

void unit_test_constructor()
{
    Rational r_default{};
    Rational r_one{25};
    Rational r_two{3, 5};
    Rational r_str{"0/30"};
    Rational r_str_bad{"cdefgabs"};

    cout << "\n===========( Constructors )==========="      << endl;
    cout << "Default        | " << r_default.to_string()    << endl;
    cout << "One param      | " << r_one.to_string()        << endl;
    cout << "Two param      | " << r_two.to_string()        << endl;
    cout << "String good    | " << r_str.to_string()        << endl;
    cout << "String bad     | " << r_str_bad.to_string()    << endl;

    cout << "\n===========( Functions )==========="           << endl;
    cout << "get_gcd()      | " << r_two.get_gcd()            << endl;
    cout << "to_string()    | " << r_two.to_string()          << endl;
    cout << "to_double()    | " << r_two.to_double()          << endl;
    cout << "is_positive()  | " << b_str(r_two.is_positive()) << endl;

    cout << "\n===========( NaN & Inf Checks )===========" << endl;
    Rational r{0, 30};
    cout << "0 divided by x:"                    << endl;
    cout << "Inf (0/30) | " << b_str(r.is_inf()) << endl;
    cout << "NaN (0/30) | " << b_str(r.is_nan()) << endl;
    r = Rational{30, 0};
    cout << "Division by 0:"                     << endl;
    cout << "Inf (30/0) | " << b_str(r.is_inf()) << endl;
    cout << "NaN (30/0) | " << b_str(r.is_nan()) << endl;
    r = Rational{0, 0};
    cout << "0 divided by 0:"                    << endl;
    cout << "Inf (0/0)  | " << b_str(r.is_inf()) << endl;
    cout << "NaN (0/0)  | " << b_str(r.is_nan()) << endl;

    cout << "\n===========( Simplification )===========" << endl;
    r = Rational(45, 5);
    cout << "(45/5) should become (9/1)    | " << r.to_string() << endl;
    r = Rational(385, 33);
    cout << "(385/33) should become (35/3) | " << r.to_string() << endl;
    r = Rational(22, -4);
    cout << "(22/-4) should become (-11/2) | " << r.to_string() << endl;

    cout << "\n===========( Math Operations )===========" << endl;
    cout << "(7/5) == (7/5)               | " << b_str(Rational{7, 5} == Rational{7, 5}) << endl;
    cout << "(3/4) + (67/-3) == (-259/12) | " << b_str(Rational{3, 4} + Rational{67, -3} == Rational{-259, 12}) << endl;
    cout << "(7/5) * (45/9) == (7/1)      | " << b_str(Rational{7, 5} * Rational{45/9} == Rational{7, 1}) << endl;
}

int main()
{
    unit_test_constructor();
    return 0;
}