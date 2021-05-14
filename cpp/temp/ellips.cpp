
#include <iostream>
#include <cstdarg>

int sum (int k, ...)
{
    va_list list;
    int s=0, x;
    va_start(list, k);
    for ( ; k!=0; k--) {
        x = va_arg(list, int);
        s+= x;
    }
    va_end(list);
    return s;
}

int main( )
{
    std::cout << "sum(2,4,6)= " << sum(2,4,6) << std::endl; // 4+6
    std::cout << "sum(4,1,2,3,4)= " << sum(4,1,2,3,4) << std::endl; // 1+2+3+4
    return 0;
}
