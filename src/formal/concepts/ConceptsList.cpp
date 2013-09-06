#include <cstdio>
#include <vector>
#include <formal/concepts/Concept.h>
#include <formal/concepts/ConceptsList.h>
#include <formal/concepts/ConceptsKeeper.h>

ConceptsList::ConceptsList( ) {
  index = 0;
  concepts = new std::vector<Concept *>;
}

ConceptsList::~ConceptsList( ) {
  Concept *c;

  while (!concepts->empty( )) {
    c = concepts->back( );
    concepts->pop_back( );

    delete c;
  }

  delete concepts;
}

bool ConceptsList::existConcept(Concept *cpt) {
  Concept *c;
  bool equal = false;
  unsigned int i = 0;

  if (!cpt)
    return true;

  while (i < concepts->size( ) && !equal) {
    c = (*concepts)[i];

    if (*cpt == *c)
      equal = true;

    i++;
  }

  return equal;
}

void ConceptsList::addConcept(Concept *cpt) {
  if (cpt)
    concepts->push_back(cpt);
}

bool ConceptsList::hasMoreConcepts( ) {
  return (index < concepts->size( ));
}

Concept *ConceptsList::nextConcept( ) {
  if (!hasMoreConcepts( ))
    return NULL;

  return (*concepts)[index++];
}

Concept *ConceptsList::getConcept(unsigned int pos) {
  Concept *ret = NULL;

  if (pos >= 0 && pos < concepts->size( ))
    ret = (*concepts)[pos];

  return ret;
}

void ConceptsList::reset( ) {
  index = 0;
}

unsigned int ConceptsList::length( ) {
  return concepts->size( );
}
