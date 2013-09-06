#ifndef _CONCEPTS_KEEPER_H
#define _CONCEPTS_KEEPER_H

#include <formal/concepts/Concept.h>

class ConceptsKeeper {
  protected:
    ConceptsKeeper( );
  public:
    virtual ~ConceptsKeeper( );
    virtual bool existConcept(Concept *cpt) = 0;
    virtual void addConcept(Concept *cpt) = 0;
    virtual bool hasMoreConcepts( ) = 0;
    virtual Concept *nextConcept( ) = 0;
    virtual Concept *getConcept(unsigned int pos) = 0;
    virtual void reset( ) = 0;
    virtual unsigned int length( ) = 0;
    virtual void freeExtraResources( );
    static ConceptsKeeper *createInstance( );
};

#endif
