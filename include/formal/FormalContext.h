#ifndef _FORMAL_CONTEXT_H
#define _FORMAL_CONTEXT_H

#include <io/BurMeister.h>
#include <util/Object.h>

#if defined(BuDDy)
  #include <bdd.h>
#elif defined(CUDD)
  #include <cudd.h>
#else
  #error "Invalid BDD Library"
#endif

class FormalContext {
  public:
    int attributes;
    int objects;
    int filled;

#if defined(BuDDy)
    bdd context;
#elif defined(CUDD)
    DdManager *ddman;
    DdNode *context;

    DdNode *zddtrue;
    DdNode *zddfalse;
#endif

    void addObject(Object &obj);

  public:
    FormalContext(int attributes);
    ~FormalContext( );

    void process(BurMeister *in);

#if defined(BuDDy)
    bdd extractAttribute(int idx);
    bdd &extractBDD( );
#elif defined(CUDD)
    DdNode *extractAttribute(int idx);
    DdNode *extractBDD( );

    DdManager *getDdManager( );
#endif

    int getAttributes( );
    int getObjects( );
    float getDensity( );
    int getSize( );
};

#endif
