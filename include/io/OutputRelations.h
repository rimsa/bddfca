#ifndef _OUTPUT_RELATIONS_H
#define _OUTPUT_RELATIONS_H

#include <fstream>
#include <extract/Relation.h>

class OutputRelations {
  private:
    std::ofstream *fd;
    const char *output;
  public:
    OutputRelations(const char *output);
    ~OutputRelations( );

    const char *getOutputName( );
    void writeRelation(Relation &rel);    
};

#endif
