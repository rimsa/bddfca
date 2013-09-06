#include <iostream>
#include <cstdio>
#include <vector>
#include <io/BurMeister.h>
#include <util/Object.h>
#include <control/Args.h>
#include <extract/Relation.h>
#include <extract/ExtractRelations.h>
#include <formal/concepts/ConceptsKeeper.h>

using namespace std;

ExtractRelations::ExtractRelations(BurMeister *input, ConceptsKeeper *keeper) {
  this->input = input;
  this->keeper = keeper;

  index = 0;
  relations = new vector<Relation *>;
}

ExtractRelations::~ExtractRelations( ) {
  Relation *rel;

  while (!relations->empty( )) {
    rel = relations->back( );
    delete rel;

    relations->pop_back( );
  }

  delete relations;
}

void ExtractRelations::process( ) {
  int i, objIndex;
  unsigned int j;
  Relation *rel;
  Concept *cpt;
  Object *obj;
  bool verbose;
  uint64_t cnt, total, last, done;

  verbose = Args::getInstance( )->getVerbose( );

  cnt = 0LL;
  last = 0LL;
  total = (uint64_t) keeper->length( ) +
          ((uint64_t) input->getObjects( ) * (uint64_t) keeper->length( ));

  while (keeper->hasMoreConcepts( )) {
    cpt = keeper->nextConcept( );

    rel = new Relation(input, cpt);
    for (i = 0; i < input->getAttributes( ); i++) {
      if (cpt->hasAttribute(i))
        rel->addIntent(i);
    }

    relations->push_back(rel);

    if (verbose) {
      cnt++;

      done = (cnt * 100) / total;
      if (done > last) {
        cout << "... " << done  << "% Done..." << endl << flush;
        last = done;
      }
    }
  }

  input->rewind( );
  
  while (input->hasMoreObjects( )) {
    objIndex = input->getCurrentObjectIndex( );
    obj = input->nextObject( );

    for (j = 0; j < relations->size( ); j++) {
      rel = relations->at(j);
      cpt = rel->getConcept( );
      if (cpt->hasObject(*obj))
        rel->addExtent(objIndex);

      if (verbose)
        cnt++;
    }

    if (verbose) {
      done = (cnt * 100) / total;
      if (done > last) {
        cout << "... " << done << "% Done..." << endl << flush;
        last = done;
      }
    }
  }
}

bool ExtractRelations::hasMoreRelations( ) {
  return (index < relations->size( ));
}

Relation *ExtractRelations::nextRelation( ) {
  if (!hasMoreRelations( ))
    return NULL;
  else
    return (*relations)[index++];
}

void ExtractRelations::reset( ) {
  index = 0;
}
