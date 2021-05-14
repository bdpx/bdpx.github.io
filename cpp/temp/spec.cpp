



double (*f)(int x);
int (* sum [5])[8];
long int * (*m1)(void);
short int * (*m2)(const char x[20]);
float (* (*m3)(int))[8];
double (* (*m4)[5])[8];


int main(void)
{
  double (* u)[10];
  double (*  & x)[10] = u;
  return 0;
}