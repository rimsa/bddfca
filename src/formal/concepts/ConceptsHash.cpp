#include <util/HashTable.h>
#include <formal/concepts/Concept.h>
#include <formal/concepts/ConceptsHash.h>
#include <formal/concepts/ConceptsList.h>
#include <control/Args.h>

ConceptsHash::ConceptsHash( ) : ConceptsList( ) {
  int hashSize = Args::getInstance( )->getHashSize( );
  if (hashSize > 0)
    ht = new HashTable(hashSize);
  else
    ht = new HashTable( );
}

ConceptsHash::~ConceptsHash( ) {
  if (ht)
    delete ht;
}

void ConceptsHash::freeExtraResources( ) {
  if (ht) {
    delete ht;
    ht = NULL;
  }
}

bool ConceptsHash::existConcept(Concept *cpt) {
  if (!ht)
    return false;
  else {
    HashCode *hc = (HashCode *) cpt;
    return ht->existElement(hc);
  } 
}

void ConceptsHash::addConcept(Concept *cpt) {
  if (ht) {
    ht->addElement(cpt);
    ConceptsList::addConcept(cpt);
  }
}
