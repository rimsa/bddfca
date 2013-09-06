#include <iostream>
#include <vector>
#include <extract/Relation.h>
#include <formal/concepts/Concept.h>

using namespace std;

Relation::Relation(BurMeister *input, Concept *cpt) {
  intent = new vector<int>;
  extent = new vector<int>;

  concept = cpt;
  this->input = input;
}

Relation::~Relation( ) {
  delete intent;
  delete extent;
}

Concept *Relation::getConcept( ) {
  return concept;
}

void Relation::addIntent(int attrValue) {
  intent->push_back(attrValue);
}

int Relation::getIntentLength( ) {
  return intent->size( );
}

int Relation::getIntent(int idx) {
  return (*intent)[idx];
}

const char *Relation::getIntentName(int idx) {
  return input->getAttributeName(this->getIntent(idx));
}

void Relation::addExtent(int objcValue) {
    extent->push_back(objcValue);
}

int Relation::getExtentLength( ) {
  return extent->size( );
}

int Relation::getExtent(int idx) {
  return (*extent)[idx];
}

const char *Relation::getExtentName(int idx) {
  return input->getObjectName(this->getExtent(idx));
}

string &Relation::toString( ) {
  int i = 0;
  static string out;

  out = "{";
  for (i = 0; i < getExtentLength( ); i++) {
    if (!i)
      out += " ";
    else
      out += ", ";

    out += getExtentName(i);
  }

  out += " } -> {";
  for (i = 0; i < getIntentLength( ); i++) {
    if (!i)
      out += " ";
    else
      out += ", ";

    out += getIntentName(i);
  }

  out += " }";

  return out;
}
