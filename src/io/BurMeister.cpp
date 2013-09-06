#include <cstdio>
#include <cstring>
#include <vector>
#include <fstream>
#include <io/BurMeister.h>
#include <io/IOException.h>
#include <util/Object.h>

using namespace std;

BurMeister::BurMeister(const char *file) {
  this->file = file;

  attributes = 0;
  objects = 0;

  attributesNames = new vector<const char *>( );
  objectsNames = new vector<const char *>( );

  index = 0;

  try {
    openFile( );

    parseHead( );

    parseObjectNames( );

    parseAttributeNames( );

    // setting start data position
    objectsStart = in->tellg( );
  } catch (IOException &ioe) {
    clean( );

    throw ioe;
  }
}

BurMeister::~BurMeister( ) {
  clean( );
}

void BurMeister::clean( ) {
  delete attributesNames;
  delete objectsNames;

  closeFile( );

  delete in;
}

int BurMeister::getAttributes( ) {
  return attributes;
}

int BurMeister::getObjects( ) {
  return objects;
}

const char *BurMeister::getAttributeName(unsigned int idx) {
  if (idx >= 0 && idx < attributesNames->size( ))
    return (*attributesNames)[idx];
  else
    return NULL;
}

const char *BurMeister::getObjectName(unsigned int idx) {
  if (idx >= 0 && idx < objectsNames->size( ))
    return (*objectsNames)[idx];
  else
    return NULL;
}

bool BurMeister::hasMoreObjects( ) {
  return (index < objects);
}

Object *BurMeister::nextObject( ) {
  int i, length;
  const char *line;

  if (!hasMoreObjects( ))
    return NULL;

  Object *ret = new Object(attributes);

  line = nextLine( );
  length = strlen(line);
  if (length > attributes)
    throw IOException("Invalid object line");

  for (i = 0; i < length; i++) {
    const char c = line[i];
    if (c != ' ' && c != 'X')
      throw IOException("Invalid burnmeister file");

    ret->set(i, (c == 'X'));
  }

  index++;

  return ret;
}

const char *BurMeister::getCurrentObjectName( ) {
  return getObjectName(index);
}

int BurMeister::getCurrentObjectIndex( ) {
  return index;
}

void BurMeister::rewind( ) {
  index = 0;
  in->seekg(objectsStart, ios::beg);
}

const char *BurMeister::nextLine( ) {
  static string line;
  unsigned int pos;

  if (!in->good( ))
    throw IOException("Premature end of file");

  getline(*in, line);

  pos = line.size( );
  while (pos > 0 && (line.at(pos - 1) == ' ' || line.at(pos - 1) == '\r'))
    pos--;

  if (pos < line.size( ))
    line.resize(pos);

  return line.c_str( );
}

void BurMeister::openFile( ) {
  in = new ifstream(file);
  if (!in->is_open( ))
    throw IOException("Unable to open input file");
}

void BurMeister::closeFile( ) {
  if (in)
    in->close( );
}

void BurMeister::emptyLine( ) {
  const char *line = nextLine( );
  if (strlen(line))
    throw IOException("Input file is not in burmeister format");
}

const char *BurMeister::filledLine( ) {
  const char *line = nextLine( );
  if (!strlen(line))
    throw IOException("Input file is not in burmeister format");

  return line;
}

int BurMeister::readInt( ) {
  const char *line = nextLine( );
  return atoi(line);
}

char *BurMeister::copyBuffer(const char *line) {
  char *dup;

  dup = strdup(line);
  if (!dup)
    throw IOException("Unable to allocate object name");

  return dup;
}

void BurMeister::parseHead( ) {
  const char *line;

  line = nextLine( );
  if (strcmp(line, "B"))
    throw IOException("Input file is not in burmeister format");

  emptyLine( );

  objects = readInt( );
  if (objects <= 0)
    throw IOException("Invalid number of objects");

  attributes = readInt( );
  if (attributes <= 0)
    throw IOException("Invalid number of attributes");

  emptyLine( );
}

void BurMeister::parseObjectNames( ) {
  int i;
  const char *line;

  for (i = 0; i < objects; i++) {
    line = filledLine( );

    objectsNames->push_back(copyBuffer(line));
  }
}

void BurMeister::parseAttributeNames( ) {
  int i;
  const char *line;

  for (i = 0; i < attributes; i++) {
    line = filledLine( );

    attributesNames->push_back(copyBuffer(line));
  }
}
