#ifndef _BUR_MEISTER_H
#define _BUR_MEISTER_H

#include <vector>
#include <fstream>
#include <util/Object.h>

class BurMeister {
  private:
    const char *file;
    int attributes;
    int objects;

    std::vector<const char *> *attributesNames;
    std::vector<const char *> *objectsNames;

    int index;

    std::ifstream *in;
    unsigned int objectsStart;

    void clean( );

    const char *nextLine( );
    bool checkLine(const char *check);

    void openFile( );
    void closeFile( );

    void emptyLine( );
    const char *filledLine( );

    int readInt( );
    char *copyBuffer(const char *line);

    void parseHead( );
    void parseObjectNames( );
    void parseAttributeNames( );
  public:
    BurMeister(const char *file);
    ~BurMeister( );

    int getAttributes( );
    int getObjects( );
    const char *getAttributeName(unsigned int idx);
    const char *getObjectName(unsigned int idx);

    bool hasMoreObjects( );
    Object *nextObject( );
    const char *getCurrentObjectName( );
    int getCurrentObjectIndex( );

    void rewind( );
};

#endif
