
#ifndef __VECTOR__
#define __VECTOR__

#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;

enum {
	ERR_NOERROR	= 0,
	ERR_NOMEM	= 1,
	ERR_OUTOFRANGE	= 2,
	ERR_DESTROYED	= 4,
	ERR_OTHER	= 8
};

class vector {
  private:
	static int global_counter;
	float	*ptr;
	int	size;
	int	state;

  public:
	static int get_global_counter(void);
	void print(ostream& out);
	~vector(void);
	vector(void);
	vector(int num);
	vector(int num, float value);

        vector& operator = (const vector& r);

	float& operator [] (int index);

	friend vector operator + (vector& x, vector & y);
	friend vector operator - (vector& x, vector & y);

	friend void operator += (vector& v, float x);
	friend void operator -= (vector& v, float x);
	friend void operator *= (vector& v, float x);

	friend bool operator == (vector& x, vector& y);
	friend bool operator != (vector& x, vector& y) { return !(x == y); }
};

#endif
