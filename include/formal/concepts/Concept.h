#ifndef _CONCEPT_H
#define _CONCEPT_H

#include <util/Object.h>
#include <util/HashCode.h>

class Concept : public HashCode {
  private:
    int used;
    int size;
    bool *attributes;
  public:
    Concept(int n);
    Concept(int n, bool full);
    Concept(Concept &cpt);
    ~Concept( );

    void setAttribute(int idx);

    bool hasAttribute(int idx);
    bool hasObject(Object &obj);

    int attributesUsed( );

    int operator==(const Concept &cpt);

    int hashCode( );
    int operator==(const HashCode *code);
};
  
#endif
