#include <util/Object.h>

Object::Object(int lngth) {
  bits = new char [lngth];
  for (int i = 0; i < lngth; i++)
    bits[i] = '0';

  this->lngth = lngth;
  this->flld = 0;
}

Object::~Object( ) {
  delete bits;
}

int Object::length( ) {
  return lngth;
}

int Object::filled( ) {
  return flld;
}

void Object::set(int idx, bool value) {
  int old = bits[idx];
  bits[idx] = (value ? '1' : '0');

  if (old != bits[idx])
    flld += (value ? 1 : -1);
}

void Object::set(int idx) {
  if (bits[idx] != '1') {
    bits[idx] = 1;
    flld++;
  }
}

bool Object::get(int idx) {
  return (bits[idx] == '1');
}

const char *Object::toString( ) {
  return bits;
}
