
#include "vector.h"

int vector::global_counter = 0;

int vector::get_global_counter(void)
{
  return global_counter;
}

vector::vector(void)
{
  ptr = new float[1];
  size = 1;
  state = ERR_NOERROR;
  ptr[0] = 0.0f;
  global_counter++;
  cout << "VOID constructor " << size << endl;
}

vector::vector(int num)
{
  ptr = new float[num];
  if (ptr == NULL) {
    cout << "Out of memory" << endl;
    state = ERR_NOMEM;
  } else {
    size = num;
    state = ERR_NOERROR;

    int i;
    for(i=0; i<num; i++) ptr[i] = i;
  }
  global_counter++;
  cout << "INDEX constructor " << num << endl;
}

vector::vector(int num, float value)
{
  ptr = new float[num];
  if (ptr == NULL) {
    cout << "Out of memory" << endl;
    state = ERR_NOMEM;
  } else {
    size = num;
    state = ERR_NOERROR;

    int i;
    for(i=0; i<num; i++) {
      ptr[i] = value;
    }
  }
  global_counter++;
  cout << "VALUE constructor " << num << endl;
}

vector::~vector(void)
{
  delete [] ptr;
  ptr = NULL;
  size = 0;
  state = ERR_DESTROYED;
  global_counter--;
}


vector& vector::operator = (const vector& r)
{
  if (ptr)
    delete [] ptr;
  size = r.size;
  ptr = new float[size];

  for(int i=0; i<size; i++) ptr[i] = r.ptr[i];
  return *this;
}


float& vector::operator [] (int index)
{
  if (index < 0 || index >= size) {
    cout << "Error! Index " << index << " is out of range [0.." << (size-1) << "]" << endl;
    cout.flush();
    exit(666);
  }
  return ptr[index];
}


void vector::print(ostream& out)
{
  if (state != ERR_NOERROR) {
    out << "Bad vector" << endl;
    return;
  }

  out << "SIZE=" << size << endl;

  for (int i=0; i<size; i++) {
     out << ptr[i] << endl;
  }
}

vector operator + (vector& x, vector & y)
{
  if (x.size != y.size) {
    cout << "Sizes not identical" << endl;
    exit(666);
  }

  vector tmp(x.size);

  for(int i=0; i<x.size; i++) tmp[i] = x[i] + y[i];
  return tmp;
}


vector operator - (vector& x, vector & y)
{
  if (x.size != y.size) {
    cout << "Sizes not identical" << endl;
    exit(666);
  }

  vector tmp(x.size);

  for(int i=0; i<x.size; i++) tmp[i] = x[i] - y[i];
  return tmp;
}


void operator += (vector& v, float x)
{
  for (int i=0; i<v.size; i++) {
     v.ptr[i] += x;
  }
}

void operator -= (vector& v, float x)
{
  for (int i=0; i<v.size; i++) {
     v.ptr[i] -= x;
  }
}

void operator *= (vector& v, float x)
{
  for (int i=0; i<v.size; i++) {
     v.ptr[i] *= x;
  }
}


bool operator == (vector& x, vector& y)
{
  if (x.size != y.size)
    return false;

  for (int i=0; i<x.size; i++) {
    if (x.ptr[i] != y.ptr[i])
      return false;
  }

  return true;
}

