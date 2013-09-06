#ifndef _FCA_H
#define _FCA_H

#include <io/BurMeister.h>
#include <io/OutputRelations.h>
#include <io/OutputStats.h>
#include <formal/FormalContext.h>
#include <formal/FormalConcept.h>
#include <extract/ExtractRelations.h>

class FCA {
  private:
    bool verbose;

    BurMeister *in;
    OutputRelations *out;
    OutputStats *stats;

    FormalContext *context;
    FormalConcept *concept;
    ExtractRelations *extract;
    
    BurMeister *loadInput(const char *input);
    OutputRelations *loadOutput(const char *output);
    OutputStats *loadStats(const char *output);

    FormalContext *assembleFormalContext( );
    FormalConcept *generateFormalConcept( );
    ExtractRelations *exportExtractRelations( );

    void showRelations( );
    void writeRelations( );
  public:
    FCA( );
    ~FCA( );

    void process( );
};

#endif
