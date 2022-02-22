#ifndef RATIONAL_H
#define RATIONAL_H

#include <string>
#include <iostream>     // For debugging, can be removed later
#include <numeric>      // For lcm

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

        Rational operator+ (const Rational & b)
        {
            int m = std::lcm(this->den_, b.den_);
            int a_num = this->num_ * (m / this->den_);
            int b_num = b.num_ * (m / b.den_);
            return Rational{a_num + b_num, m};
        }

        Rational operator- (const Rational & b)
        {
            return Rational{};
        }
        
        Rational operator/ (const Rational & b)
        {
            return Rational{};
        }

        Rational operator* (const Rational & b)
        {
            int p = this->num_ * b.num_;
            int q = this->den_ * b.den_;
            return Rational{p, q};
        }
        
        bool operator == (const Rational & b)
        {
            if((this->num_ == b.num_) && (this->den_ == b.den_)) return true;
            return false;
        }

    private:
        void compile();
        void flip_sign();
        void try_simplify();
        int num_, den_;
        double decimal_;
};

// should overload the following: add, subtract, multiply & divide

#endif