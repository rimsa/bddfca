#include <cstdio>
#include <control/Args.h>

Args *Args::instance = NULL;

Args::Args( ) {
  input = stats = NULL;
  verbose = false;

  concept = false;

  extract = false;
  output = NULL;
  show = false;

  hash = false;
  hashSize = 0;
}

Args::~Args( ) {
  instance = NULL;
}

Args *Args::getInstance( ) {
  if (!instance)
    instance = new Args( );

  return instance;
}

void Args::setInput(char *input) {
  this->input = input;
}

const char *Args::getInput( ) {
  return input;
}

void Args::setStats(char *stats) {
  this->stats = stats;
}

const char *Args::getStats( ) {
  return stats;
}

void Args::setVerbose(bool verbose) {
  this->verbose = verbose;
}

bool Args::getVerbose( ) {
  return verbose;
}

void Args::setConcept(bool concept) {
  this->concept = concept;
}

bool Args::getConcept( ) {
  return concept;
}

void Args::setExtract(bool extract) {
  this->extract = extract;
}

bool Args::getExtract( ) {
  return extract;
}

void Args::setOutput(char *output) {
  this->output = output;
}

const char *Args::getOutput( ) {
  return output;
}

void Args::setShow(bool show) {
  this->show = show;
}

bool Args::getShow( ) {
  return show;
}

void Args::setHash(bool hash) {
  this->hash = hash;
}

bool Args::getHash( ) {
  return hash;
}

void Args::setHashSize(int hashSize) {
  this->hashSize = hashSize;
}

int Args::getHashSize( ) {
  return hashSize;
}
