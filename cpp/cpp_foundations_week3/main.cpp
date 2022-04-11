/*
    Week 3 assignment C++ foundations
    By Jesse Visscher, 477437, ETI1v.B'

    Rationals: https://en.wikipedia.org/wiki/Rational_number
    
    > About Get() Set():
    I usually write in the form of: thisIsAVar & ThisIsAFunc() but I try im_a_func() today.
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
#include "rationalProcess.cc"

using std::cout;
using std::cin;
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
    cout << "(45/5) should become (9/1)    | " << Rational{45, 5}.to_string() << endl;
    cout << "(385/33) should become (35/3) | " << Rational{385, 33}.to_string() << endl;
    cout << "(22/-4) should become (-11/2) | " << Rational{22, -4}.to_string() << endl;

    cout << "\n===========( Math Operations )===========" << endl;
    cout << "(7/5) == (7/5)                   | " << b_str(Rational{7, 5} == Rational{7, 5}) << endl;
    cout << "(3/4) + (67/-3) == (-259/12)     | " << b_str(Rational{3, 4} + Rational{67, -3} == Rational{-259, 12}) << endl;
    cout << "(7/5) * (45/9) == (7/1)          | " << b_str(Rational{7, 5} * Rational{45/9} == Rational{7, 1}) << endl;
    cout << "(-143/57) / (32/9) == (-429/608) | " << b_str(Rational{-143, 57} / Rational{32, 9} == Rational{-429, 608}) << endl;
    cout << "(10/8) - (0/3) == (5/4)          | " << b_str(Rational{10, 8} - Rational{0, 3} == Rational{5, 4}) << endl;
    cout << "(5/6).pow(2) == (25/36)          | " << b_str(Rational{5, 6}.pow(2) == Rational{25, 36}) << endl;
}

enum Option { EXPRESSION = 1, FILE_PROCESS, QUIT };

int parseInt()
{
    int n;
    while (!(std::cin >> n) || n > 3) {
        std::cin.clear();
        std::string line;
        std::getline(std::cin, line);
        if (line == "") {
            std::cout << n << " is not a valid option";
        } else {
            std::cout << line << " is not a number";
        }
        std::cout << ", please try again: ";
    }
    return n;
}

ifstream appendStream()
{
    ifstream stream{};
    string path{};

    cout << "Please enter a valid file path: ";
    getline(cin, path);
    getline(cin, path);
    while ((stream = ifstream{path}).is_open() == false) {
        cout << "file '"<< path << "' could not be found, please try again: ";
        getline(cin, path);
    }

    cout << "Opening '" << path << "'" << std::endl;
    return stream;
}

void handleExpression()
{
    cout << "Please enter rational expression: ";
    string line{};
    std::getline(std::cin, line);
    std::getline(std::cin, line);
    auto result = Rational::calculate(line);
    cout << line << " = " << result.to_string() << std::endl;
}

void handleFileProcess()
{
    auto stream = appendStream();
    RationalProcess::process(stream);
    cout << "Successfully wrote output to './files/out.txt'\n";
}

int main()
{
    bool stay = true;

    while (stay) {
        cout << "Please select option: (1. Expressions - 2. File processing - 3. Quit): ";
        Option option = (Option) parseInt();

        switch(option) {
            case EXPRESSION:
                handleExpression();
                break;
            case FILE_PROCESS:
                handleFileProcess();
                break;
            case QUIT:
                stay = false;
                break;
        }
    }

    cout << "Thank you and goodbye!";
    return 0;
}