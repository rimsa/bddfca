#ifndef _CONCEPTS_HASH_H
#define _CONCEPTS_HASH_H

#include <util/HashTable.h>
#include <formal/concepts/Concept.h>
#include <formal/concepts/ConceptsList.h>

class ConceptsHash : public ConceptsList {
  private:
    HashTable *ht;
  public:
    ConceptsHash( );
    ~ConceptsHash( );
    virtual bool existConcept(Concept *cpt);
    virtual void addConcept(Concept *cpt);
    virtual void freeExtraResources( );
};

#endif
