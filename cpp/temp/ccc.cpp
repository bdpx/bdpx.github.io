
#include "vector.h"

int main(void)
{
  cout << "Hello" << endl;

  vector x;
  vector y(5);
  vector z(5, 2.0);
  vector d(5, 2.0);

  cout << "I create " << vector::get_global_counter() << " objects of class vector" << endl;

  x.print(cout);
  y.print(cout);
  z.print(cout);

  if (y == z) 
    cout << "z equal y" << endl;
  else
    cout << "z not equal y" << endl;

  if (z != d) 
    cout << "z not equal d" << endl;
  else
    cout << "z equal d" << endl;

  z += 4.0;
  z.print(cout);

  z -= 2.5;
  z.print(cout);

  z *= 2.0;
  z.print(cout);

  z[3] = 8.0;
  z.print(cout);

  z = y + d;
  z.print(cout);

  z = d - y;
  z.print(cout);

  z[5] = 56.0; // ERROR
  z.print(cout);

  return 0;
}
