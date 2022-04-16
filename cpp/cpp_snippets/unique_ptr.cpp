// Unique pointer example

#include <iostream>
#include <memory>

using namespace std;

int main()
{
    const int arr_size = 5;
    std::unique_ptr<int[]> ptr(new int[arr_size]);
    
    for (int i = 0; i < arr_size; i++) {
        ptr[i] = i * i;
    }
    
    for (int i = 0; i < arr_size; i++) {
        std::cout << i << ": " << ptr[i] << std::endl;
    }

    return 0;
}
