
#include <iostream.h>

struct AA {
virtual void f() {std::cout << "f" << std::endl;}
int i; 
};

struct BB: public AA {
void f() = 0;
};

struct CC: public BB {
void f() {std::cout << "f" << ":" << i << std::endl;}
};

void my_func()
{
AA* pa = new CC;
pa -> f();
} 


struct A { virtual void f(void)=0; };

void A::f(void) {std::cout << "A" << std::endl;}

struct B : public A { void f(void); };

void B::f(void) {A::f(); std::cout << "B" << std::endl; }

int main(void) {B *b=new B; b->f();

my_func();

 return 0;} 