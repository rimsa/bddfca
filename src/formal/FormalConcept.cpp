#include <iostream>
#include <cstdio>
#include <vector>
#include <control/Args.h>
#include <formal/FormalConcept.h>
#include <formal/concepts/Concept.h>
#include <formal/concepts/ConceptsKeeper.h>

using namespace std;

FormalConcept::FormalConcept(FormalContext *context) {
  this->attr = context->getAttributes( );
  this->context = context;
  this->concepts = ConceptsKeeper::createInstance( );

#if defined CUDD
  ddman = context->getDdManager( );

  zddtrue = Cudd_ReadZddOne(ddman, 0);
  Cudd_Ref(zddtrue);

  zddfalse = Cudd_zddDiff(ddman, zddtrue, zddtrue);
  Cudd_Ref(zddfalse);
#endif
}

FormalConcept::~FormalConcept( ) {
#if defined CUDD
	  Cudd_Deref(zddtrue);
	  Cudd_Deref(zddfalse);
#endif

  delete concepts;
}

void FormalConcept::process( ) {
  int i;
  unsigned int j, size;
  int cnt, partial, total;
  int done, last;
  bool verbose;

#if defined BuDDy
  bdd &ctx = context->extractBDD( );
#elif defined CUDD
  DdNode *ctx = context->extractBDD( );
#endif

  Concept *all = this->createConcept(ctx);
  concepts->addConcept(all);

#if defined CUDD
  Cudd_RecursiveDerefZdd(ddman, ctx);
#endif

  cnt = 0;
  last = 0;
  verbose = Args::getInstance( )->getVerbose( );

  for (i = 0; i < attr; i++) {
#if defined BuDDy
    bdd tmp1 = context->extractAttribute(i);
#elif defined CUDD
    DdNode *tmp1 = context->extractAttribute(i);
#endif

    size = concepts->length( );
    for (j = 0; j < size; j++) {
      Concept *cpt = concepts->getConcept(j);

#if defined BuDDy
      bdd tmp2 = this->assemblyBDD(cpt);
      bdd intersec = tmp1 & tmp2;
#elif defined CUDD
      DdNode *tmp2 = this->assemblyBDD(cpt);
      DdNode *intersec = Cudd_zddIntersect(ddman, tmp1, tmp2);

      Cudd_Ref(intersec);
      Cudd_RecursiveDerefZdd(ddman, tmp2);
#endif

      Concept *out = this->createConcept(intersec);
      if (!concepts->existConcept(out))
        concepts->addConcept(out);
      else
        delete out;

#if defined CUDD
      Cudd_RecursiveDerefZdd(ddman, intersec);
#endif

      if (verbose) {
        partial = cnt + j + 1;
        total = cnt + size + ((attr - i - 1) * concepts->length( ));

        done = (100 * partial) / total;
        if (done != last) {
          std::cout << "... " << done << "% Done..." << std::endl << std::flush;
          last = done;
        }
      }
    }

    cnt += size;

#if defined CUDD
    Cudd_RecursiveDerefZdd(ddman, tmp1);
#endif
  }

  concepts->freeExtraResources( );
}

ConceptsKeeper *FormalConcept::getConceptsKeeper( ) {
  return concepts;
}

unsigned int FormalConcept::getLength( ) {
  return concepts->length( );
}

#if defined BuDDy
Concept *FormalConcept::createConcept(const bdd &base) {
#elif defined CUDD
Concept *FormalConcept::createConcept(DdNode *base) {
#endif
  int i;

  Concept *cpt = NULL;

#if defined BuDDy
  if (base == bddfalse)
#elif defined CUDD
  if (base == zddfalse)
#endif
	  cpt = new Concept(attr, true);
  else {
    cpt = new Concept(attr);
    for (i = 0; i < attr; i++) {
#if defined BuDDy
       bdd tmp = base & bdd_ithvar(i);
#elif defined CUDD
       DdNode *var = Cudd_zddIthVar(ddman, i);
       Cudd_Ref(var);

       DdNode *tmp = Cudd_zddIntersect(ddman, base, var);
       Cudd_Ref(tmp);
#endif

       if (tmp == base)
         cpt->setAttribute(i);

#if defined CUDD
       Cudd_RecursiveDerefZdd(ddman, var);
       Cudd_RecursiveDerefZdd(ddman, tmp);
#endif
    }
  }

  return cpt;
}

#if defined BuDDy
bdd FormalConcept::assemblyBDD(Concept *cpt) {
#elif defined CUDD
DdNode *FormalConcept::assemblyBDD(Concept *cpt) {
#endif
  int i;

#if defined BuDDy
  bdd ret = context->extractBDD( );
#elif defined CUDD
  DdNode *ret = context->extractBDD( );
#endif

  for (i = 0; i < attr; i++) {
    if (cpt->hasAttribute(i)) {
#if defined BuDDy
      ret &= bdd_ithvar(i);
#elif defined CUDD
      DdNode *var = Cudd_zddIthVar(ddman, i);
      Cudd_Ref(var);

      DdNode *tmp = Cudd_zddIntersect(ddman, ret, var);
      Cudd_Ref(tmp);

      Cudd_RecursiveDerefZdd(ddman, var);
      Cudd_RecursiveDerefZdd(ddman, ret);
      ret = tmp;
#endif
    }
  }

  return ret;
}
