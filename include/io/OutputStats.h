#ifndef _OUTPUT_STATS_H
#define _OUTPUT_STATS_H

#include <fstream>

class OutputStats {
  private:
    const char *file;
    std::ofstream *out;
  public:
    OutputStats(const char *file);
    ~OutputStats( );

    void writeHeader(int attributes, int objects);
    void writeContext(float formalContextDensity, int formalContextSize, double formalContextTime);
    void writeConcept(unsigned int formalConceptLength, double formalConceptTime);
    void writeExtract(double extractConceptsTime);

};

#endif
