#include <cstdio>
#include <control/Args.h>
#include <formal/concepts/ConceptsHash.h>
#include <formal/concepts/ConceptsList.h>
#include <formal/concepts/ConceptsKeeper.h>

ConceptsKeeper::ConceptsKeeper( ) {
}

ConceptsKeeper::~ConceptsKeeper( ) {
}

void ConceptsKeeper::freeExtraResources( ) {
}

ConceptsKeeper *ConceptsKeeper::createInstance( ) {
  ConceptsKeeper *ck = NULL;
  Args *args = Args::getInstance( );

  if (args->getHash( ))
    ck = new ConceptsHash( );
  else
    ck = new ConceptsList( );

  return ck;
}
