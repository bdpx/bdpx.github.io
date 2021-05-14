#include <iostream.h>
#include <fstream.h>
#include <strstream.h>

int main(void)
{
  int n;
 ifstream f("data.txt");
 f >> n;
 cout << n << endl;

// ofstream o("temp.txt");
 cout << hex << showpos << n << endl;

 char str[200];

 strstream s(str, 200);
 s << n << ' ';
 s << n << endl;

 cout << s.str();
 return 0;
}
