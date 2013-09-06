#ifndef _CONCEPTS_LIST_H
#define _CONCEPTS_LIST_H

#include <vector>
#include <formal/concepts/Concept.h>
#include <formal/concepts/ConceptsKeeper.h>

class ConceptsList : public ConceptsKeeper {
  private:
    unsigned int index;
    std::vector<Concept *> *concepts;
  public:
    ConceptsList( );
    virtual ~ConceptsList( );
    bool existConcept(Concept *cpt);
    void addConcept(Concept *cpt);
    bool hasMoreConcepts( );
    Concept *nextConcept( );
    Concept *getConcept(unsigned int pos);
    void reset( );
    unsigned int length( );
};

#endif
