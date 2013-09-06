#ifndef _FORMAL_CONCEPT_H
#define _FORMAL_CONCEPT_H

#include <vector>
#include <formal/FormalContext.h>
#include <formal/concepts/Concept.h>
#include <formal/concepts/ConceptsKeeper.h>

#if defined BuDDy
  #include <bdd.h>
#elif defined CUDD
  #include <cudd.h>
#endif

class FormalConcept {
  private:
    int attr;
    FormalContext *context;
    ConceptsKeeper *concepts;

#if defined BuDDy
    Concept *createConcept(const bdd &base);
    bdd assemblyBDD(Concept *cpt);
#else defined CUDD
    DdManager *ddman;
    DdNode *zddtrue;
    DdNode *zddfalse;

    Concept *createConcept(DdNode *base);
    DdNode *assemblyBDD(Concept *cpt);
#endif

  public:
    FormalConcept(FormalContext *context);
    ~FormalConcept( );

    void process( );
    ConceptsKeeper *getConceptsKeeper( );
    unsigned int getLength( );

};

#endif
