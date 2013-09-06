#include <iostream>
#include <iomanip>
#include <cstdio>
#include <io/BurMeister.h>
#include <io/OutputRelations.h>
#include <io/OutputStats.h>
#include <io/IOException.h>
#include <formal/FormalContext.h>
#include <formal/FormalConcept.h>
#include <control/FCA.h>
#include <control/Args.h>
#include <time/TimeHandler.h>

using namespace std;

FCA::FCA( ) {
  in = NULL;
  out = NULL;
  context = NULL;
  concept = NULL;
  extract = NULL;
  stats = NULL;
}

FCA::~FCA( ) {
  verbose = false;

  if (in)
    delete in;

  if (out)
    delete out;  

  if (stats)
    delete stats;

  if (context)
    delete context;

  if (concept)
    delete concept;

  if (extract)
    delete extract;
}

void FCA::process( ) {
  Args *args = Args::getInstance( );

  verbose = args->getVerbose( );

  in = loadInput(args->getInput( ));
  out = loadOutput(args->getOutput( ));
  stats = loadStats(args->getStats( ));

  context = assembleFormalContext( );

  if (args->getConcept( )) {
    concept = generateFormalConcept( );

    if (args->getExtract( )) {
      extract = exportExtractRelations( );

      // show relations
      if (args->getShow( ))
        showRelations( );

      // write relations
      if (out)
        writeRelations( );
    }
  }
}

BurMeister *FCA::loadInput(const char *input) {
  return new BurMeister(input);
}

OutputRelations *FCA::loadOutput(const char *output) {
  if (!output)
    return NULL;
  else
    return new OutputRelations(output);
}

OutputStats *FCA::loadStats(const char *output) {
  OutputStats *os = NULL;
  if (output) {
    os = new OutputStats(output);
    os->writeHeader(in->getAttributes( ), in->getObjects( ));
  }

  return os;
}

FormalContext *FCA::assembleFormalContext( ) {
  double tm;
  FormalContext *ctx = new FormalContext(in->getAttributes( ));

  if (verbose)
    cout << "Applying BDD..." << endl << flush;

  TimeHandler th1 = TimeHandler::getCurrentTime( );
  ctx->process(in);
  TimeHandler th2 = TimeHandler::getCurrentTime( );

  th2 -= th1;
  tm = th2.getTime( );

  if (verbose)
    cout << setprecision(6) << "... 100% Done in " << tm << " secounds" << endl << flush;

  if (stats)
    stats->writeContext(ctx->getDensity( ), ctx->getSize( ), tm);

  return ctx;
}

FormalConcept *FCA::generateFormalConcept( ) {
  double tm;
  FormalConcept *fcpt = new FormalConcept(context);

  if (verbose)
    cout << endl << "Generating Formal Concepts..." << endl << flush;

  TimeHandler th1 = TimeHandler::getCurrentTime( );
  fcpt->process( );
  TimeHandler th2 = TimeHandler::getCurrentTime( );

  th2 -= th1;
  tm = th2.getTime( );

  if (verbose)
    cout << setprecision(6) << "... 100% Done in " << tm << " secounds" << endl << flush; 

  if (stats)
    stats->writeConcept(fcpt->getLength( ), tm);

  return fcpt;
}

ExtractRelations *FCA::exportExtractRelations( ) {
  double tm;
  ExtractRelations *er;

  if (verbose)
    cout << endl << "Extracting Relations..." << endl << flush;

  er = new ExtractRelations(in, concept->getConceptsKeeper( ));

  TimeHandler th1 = TimeHandler::getCurrentTime( );
  er->process( );
  TimeHandler th2 = TimeHandler::getCurrentTime( );

  th2 -= th1;
  tm = th2.getTime( );

  if (verbose)
    cout << setprecision(6) << "... 100% Done in " << tm << " secounds" << endl << flush;

  if (stats)
    stats->writeExtract(tm);

  return er;
}

void FCA::showRelations( ) {
  int i = 1;
  Relation *rel;

  if (verbose)
    cout << endl << "Showing all set of concepts:" << endl << flush;

  extract->reset( );

  while (extract->hasMoreRelations( )) {
    rel = extract->nextRelation( );

    if (verbose)
      cout << "  ";

    cout << "Relation " << i << ": " << rel->toString( ) << endl << flush;

    i++;
  }
}

void FCA::writeRelations( ) {
  Relation *rel;

  extract->reset( );

  while (extract->hasMoreRelations( )) {
    rel = extract->nextRelation( );
    out->writeRelation(*rel);
  }
}
