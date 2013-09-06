#include <iostream>
#include <fstream>
#include <iomanip>
#include <io/OutputStats.h>
#include <io/IOException.h>

using namespace std;

OutputStats::OutputStats(const char *file) {
  this->file = file;

  out = new ofstream(file);
  if (!out->is_open( ))
    throw new IOException("Unable to open statistics output file");
}

OutputStats::~OutputStats( ) {
  out->close( );
  delete out;
}

void OutputStats::writeHeader(int attributes, int objects) {
  *out << fixed;
  *out << "Attributes: " << attributes << endl;
  *out << "Objects: " << objects << endl;
  *out << endl << flush;
}

void OutputStats::writeContext(float formalContextDensity, int formalContextSize, double formalContextTime) {
  *out << fixed;
  *out << "Formal Context Density: " << formalContextDensity << endl;
  *out << "Formal Context Size: " << formalContextSize << endl;
  *out << "Formal Context Time: " << setprecision(6) << formalContextTime << endl;
  *out << endl << flush;
}

void OutputStats::writeConcept(unsigned int formalConceptLength, double formalConceptTime) {
  *out << fixed;
  *out << "Formal Concept Length: " << formalConceptLength << endl;
  *out << "Formal Concept Time: " << setprecision(6) << formalConceptTime << endl;
  *out << endl << flush;
}

void OutputStats::writeExtract(double extractConceptsTime) {
  *out << fixed;
  *out << "Extract Concepts Time: " << setprecision(6) << extractConceptsTime << endl;
  *out << endl << flush;
}
