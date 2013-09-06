#ifndef _RELATION_H
#define _RELATION_H

#include <vector>
#include <io/BurMeister.h>
#include <formal/concepts/Concept.h>

class Relation {
  private:
    std::vector<int> *intent;
    std::vector<int> *extent;

    Concept *concept;
    BurMeister *input;
  public:
    Relation(BurMeister *input, Concept *cpt);
    ~Relation( );

    Concept *getConcept( );

    void addIntent(int attrValue);
    int getIntentLength( );
    int getIntent(int idx);
    const char *getIntentName(int idx);

    void addExtent(int objcValue);
    int getExtentLength( );
    int getExtent(int idx);
    const char *getExtentName(int idx);

    std::string &toString( );
};

#endif
