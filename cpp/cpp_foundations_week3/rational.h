#ifndef RATIONAL_H
#define RATIONAL_H

#include <string>

using std::string;

class Rational
{
    public:
        Rational(int num, int den);
        Rational(int num);
        Rational();
        Rational(string expr);

        const int & num() const { return num_; }    // Let's create inlines for trivial get/set
        const int & den() const { return den_; }
        const double & dec() const { return decimal_; }
        // void num(const int & num) { num_ = num; }
        // void den(const int & den) { den_ = den; }

        int get_gcd();

        string to_string();
        double to_double();
        
        bool is_positive();                         // Why would I also need is_negative???
        bool is_inf();
        bool is_nan();

    private:
        int num_, den_;
        double decimal_;
};

#endif