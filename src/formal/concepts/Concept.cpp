#include <util/Object.h>
#include <formal/concepts/Concept.h>

Concept::Concept(int n) {
  int i;

  this->size = n;
  this->used = 0;

  attributes = new bool [n];

  for (i = 0; i < n; i++)
    attributes[i] = false;
}

Concept::Concept(int n, bool full) {
  int i;

  this->size = n;
  this->used = (full ? n : 0);

  attributes = new bool [n];

  for (i = 0; i < n; i++)
    attributes[i] = full;
}

Concept::Concept(Concept &cpt) {
  int i;

  this->size = cpt.size;
  this->used = cpt.used;

  this->attributes = new bool [this->size];
  for (i = 0; i < this->size; i++)
    this->attributes[i] = cpt.attributes[i];
}

Concept::~Concept( ) {
  delete attributes;
}

void Concept::setAttribute(int idx) {
  if (idx < size && !attributes[idx]) {
    attributes[idx] = true;
    used++;
  }
}

bool Concept::hasAttribute(int idx) {
  if (idx < size)
    return attributes[idx];
  else
    return false;
}

bool Concept::hasObject(Object &obj) {
  int i;

  for (i = 0; i < size; i++) {
    if (attributes[i] && !obj.get(i))
      return false;
  }

  return true;
}

int Concept::attributesUsed( ) {
  return used;
}

int Concept::operator==(const Concept &cpt) {
  register int i;

  if (size != cpt.size)
    return 0;
  else {
    for (i = 0; i < size; i++) {
      if (attributes[i] != cpt.attributes[i])
        return 0;
    }

    return 1;
  }
}

int Concept::hashCode( ) {
  int i, value;
  int hash = 0, prev = 1;

  for (i = 0; i < size; i++) {
    value = attributes[i];
    if (value) {
      hash += i * prev * value;
      prev = value;
      i++;
    }
  }

  return hash;
}

int Concept::operator==(const HashCode *code) {
  Concept *cpt = (Concept *) code;
  return (*this == *cpt);
}
