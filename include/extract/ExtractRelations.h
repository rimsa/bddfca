#ifndef _EXTRACT_RELATIONS_H
#define _EXTRACT_RELATIONS_H

#include <vector>

#include <io/BurMeister.h>
#include <extract/Relation.h>
#include <formal/concepts/ConceptsKeeper.h>

class ExtractRelations {
  private:
    BurMeister *input;
    ConceptsKeeper *keeper;

    unsigned int index;
    std::vector<Relation *> *relations;
  public:
    ExtractRelations(BurMeister *input, ConceptsKeeper *keeper);
    ~ExtractRelations( );

    void process( );

    bool hasMoreRelations( );
    Relation *nextRelation( );

    void reset( );
};

#endif
