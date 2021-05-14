
#include <iostream.h>

int main(void)
{
  static char s[] = "qqq";
  static const char cs[] = "ccc";

  try {
    try {
      throw cs;
    } catch (const char *err) {
      cout << "First:" << err << endl;
      throw;
    }
  } catch (const char *err) {
    cout << "Second:" << err << endl;
  }

  return (0);
}
