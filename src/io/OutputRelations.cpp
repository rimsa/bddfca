#include <fstream>
#include <io/IOException.h>
#include <io/OutputRelations.h>

using namespace std;

OutputRelations::OutputRelations(const char *output) {
  this->output = output;

  fd = new ofstream(output);
  if (!fd->is_open( ))
    throw IOException("Unable to open output file");
}

OutputRelations::~OutputRelations( ) {
  fd->close( );
  delete fd;
}

const char *OutputRelations::getOutputName( ) {
  return output;
}

void OutputRelations::writeRelation(Relation &rel) {
  *fd << rel.toString( ) << endl;
}
