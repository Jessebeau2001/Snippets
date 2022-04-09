/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <stdarg.h>

using std::cout;

class Sensor
{
    public:
        Sensor(int count, ...)
        {
            va_list va;
            pins = new int(count);
            pin_count = count;
            va_start(va, count);
            for(int i = 0; i < count; i++) {
                pins[i] = va_arg(va, int);
            }
            va_end(va);
        }
        
        ~Sensor()
        {
            delete[] pins;
        }
        
        void print()
        {
            std::cout << "(Pins: {";
            for (int i = 0; i < pin_count - 1; i++) {
                std::cout << pins[i] << ", ";
            }
            std::cout << pins[pin_count - 1] << "})";
        }
    
    // private:
        int * pins;
        int pin_count;
};

int * my_test_func()
{
    Sensor sens = Sensor(2, 8, 9);
    sens.print();
    
    cout << "\n" << sens.pins << "\n";
    return sens.pins;
}

int main()
{
    int * test = my_test_func();
    
    cout << test[0];    // This line shows whether the pins* var within the test_func scope has been deleted
    return 0;
}
