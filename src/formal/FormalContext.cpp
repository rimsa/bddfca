#include <iostream>
#include <cstdio>

#include <io/BurMeister.h>
#include <formal/FormalContext.h>
#include <control/Args.h>
#include <util/Object.h>

#if defined(BuDDy)
    // each node on the BuDDy algorithm uses 20 bytes
    #define NODE_SIZE 20
 
    // definition to handle file sizes easily
    #define KB * 1024
    #define MB * 1024 KB
  
    // some BuDDy initial values
    #define MIN_NODE_NUM          10 MB / NODE_SIZE
    #define MAX_NODE_NUM         100 MB / NODE_SIZE
    #define DEFAULT_CACHE_SIZE    10 MB / NODE_SIZE
    #define MAX_INCREASE           5 MB / NODE_SIZE
    #define CACHE_RATIO           64
#elif defined(CUDD)
  #include <cuddInt.h>
#endif

FormalContext::FormalContext(int attributes) {
  this->attributes = attributes;
  this->objects = 0;
  this->filled = 0;

#if defined(BuDDy)
  bdd_init(MAX_NODE_NUM, DEFAULT_CACHE_SIZE);
  bdd_setcacheratio(CACHE_RATIO);
  bdd_setmaxincrease(MAX_INCREASE);

  bdd_setvarnum(attributes);

  this->context = bddfalse;
#elif defined(CUDD)
  ddman = Cudd_Init(0, attributes, CUDD_UNIQUE_SLOTS, CUDD_CACHE_SLOTS, 0);

  cuddGarbageCollect(ddman, 1);

  zddtrue = Cudd_ReadZddOne(ddman, 0);
  Cudd_Ref(zddtrue);

  zddfalse = Cudd_zddDiff(ddman, zddtrue, zddtrue);
  Cudd_Ref(zddfalse);

  context = zddfalse;
  Cudd_Ref(context);

  // Keep track of the same variables in ZDD and BDD.
//  Cudd_AutodynDisable(ddman);
//  Cudd_AutodynDisableZdd(ddman);
//  Cudd_bddRealignEnable(ddman);
//  Cudd_zddRealignEnable(ddman);

#endif
}

FormalContext::~FormalContext( ) {
#if defined(BuDDy)
  bdd_done( );
#elif defined(CUDD)
  printf("----- WITH ZDD ------\n");
  cuddGarbageCollect(ddman, 0);
  Cudd_PrintInfo(ddman, stdout);

  printf("----- WITH BDD ------\n");
  Cudd_zddVarsFromBddVars(ddman, 1);
  DdNode* xxx = Cudd_zddPortToBdd(ddman, this->context);
  Cudd_Ref(xxx);

  Cudd_RecursiveDerefZdd(ddman, this->context);
  this->context = NULL;

  cuddGarbageCollect(ddman, 0);
  Cudd_PrintInfo(ddman, stdout);

  Cudd_RecursiveDeref(ddman, xxx);

//  Cudd_RecursiveDerefZdd(ddman, zddtrue);
//  Cudd_RecursiveDerefZdd(ddman, zddfalse);

//  Cudd_RecursiveDerefZdd(ddman, context);
//  context = NULL;

  Cudd_Quit(ddman);
#endif
}

void FormalContext::addObject(Object &obj) {
#if defined(BuDDy)
  int i;

  bdd tmp = bddtrue;

  for (i = 0; i < obj.length( ); i++) {
    if (obj.get(i))
      tmp &= bdd_ithvar(i);
    else
      tmp &= bdd_nithvar(i);
  }

  context |= tmp;
  filled += obj.filled( );

  objects++;
#elif defined(CUDD)
  int i;
  DdNode *zddObj = NULL, *var, *tmp, *tmp2;

  zddObj = zddfalse;
  Cudd_Ref(zddObj);
  
  for (i = 0; i < attributes; i++) {
    if (!obj.get(i)) {
      var = Cudd_zddIthVar(ddman, i);
      Cudd_Ref(var);

      tmp = Cudd_zddUnion(ddman, zddObj, var);
      Cudd_Ref(tmp);

      Cudd_RecursiveDerefZdd(ddman, var);
      Cudd_RecursiveDerefZdd(ddman, zddObj);

      zddObj = tmp;  
    }
  }

  tmp = Cudd_zddDiff(ddman, zddtrue, zddObj);
  Cudd_Ref(tmp);
  Cudd_RecursiveDerefZdd(ddman, zddObj);
  zddObj = tmp;
  
  for (i = 0; i < attributes; i++) {
    if (obj.get(i)) {
      var = Cudd_zddIthVar(ddman, i);
      Cudd_Ref(var);

      tmp = Cudd_zddIntersect(ddman, zddObj, var);
      Cudd_Ref(tmp);

      Cudd_RecursiveDerefZdd(ddman, var);
      Cudd_RecursiveDerefZdd(ddman, zddObj);

      zddObj = tmp;
    }
  }

  /* add the objet to the context */
  tmp2 = Cudd_zddUnion(ddman, context, zddObj);
  Cudd_Ref(tmp2);

  Cudd_RecursiveDerefZdd(ddman, context);
  Cudd_RecursiveDerefZdd(ddman, zddObj);

  context = tmp2;

  filled += obj.filled( );

  objects++;
#endif
}

void FormalContext::process(BurMeister *in) {
  int cnt, last, done;
  bool verbose;

  cnt = 0;
  last = 0;
  verbose = Args::getInstance( )->getVerbose( );

  while (in->hasMoreObjects( )) {
    Object *obj = in->nextObject( );
    this->addObject(*obj);
    delete obj;

    if (verbose) {
      cnt++;

      done = (100 * cnt) / in->getObjects( );
      if (done > last) {
        std::cout << "... " << done << "% Done..." << std::endl;
        last = done;
      }
    }
  }
}

#if defined(BuDDy)
bdd FormalContext::extractAttribute(int idx) {
  return (context & bdd_ithvar(idx));
}
#elif defined(CUDD)
DdNode *FormalContext::extractAttribute(int idx) {
  DdNode *var = Cudd_zddIthVar(ddman, idx);
  Cudd_Ref(var);

  DdNode *ret = Cudd_zddIntersect(ddman, context, var);
  Cudd_Ref(ret);

  Cudd_RecursiveDerefZdd(ddman, var);

  return ret;
}
#endif

#if defined(BuDDy)
bdd &FormalContext::extractBDD( ) {
  return context;
}
#elif defined(CUDD)
DdNode *FormalContext::extractBDD( ) {
  Cudd_Ref(context);
  return context;
}
#endif

#if defined(CUDD)
DdManager *FormalContext::getDdManager( ) {
  return ddman;
}
#endif

int FormalContext::getAttributes( ) {
  return attributes;
}

int FormalContext::getObjects( ) {
  return objects;
}

float FormalContext::getDensity( ) {
  return (((float) filled) / (attributes * objects));
}

int FormalContext::getSize( ) {
#if defined(BuDDy)
  return (NODE_SIZE * bdd_nodecount(context));
#elif defined(CUDD)
  return Cudd_ReadMemoryInUse(ddman);
#endif
}
