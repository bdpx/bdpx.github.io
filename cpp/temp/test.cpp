
#include <iostream.h>

class base {
  public:
    int xxx;

    base(int xx) { xxx = xx;  cout << "base" << endl; }
};

class base2 : virtual public base {
  public:
    int x;

    base2(int xx):base(xx+1) { x = xx;  cout << "base2" << endl; }
};

class base3 : virtual public base {
  public:
    mutable int x;

    base3(int xx):base(xx+1) { x = xx;  cout << "base3" << endl; }
};


class derived : public base2, public base3 {
  public:
    int y;
    derived(int xx, int yy) : base2(xx+1), base3(xx+3),base(xx+4) { y = yy+10;  cout << "derived" << endl; }

};

int main(void)
{
  derived xxx(8,9);

  cout << xxx.base2::xxx << " " << xxx.base3::xxx << " " << sizeof(xxx) << endl;

  return 0;
}
