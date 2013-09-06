#include <iostream>
#include <unistd.h>
#include <io/IOException.h>
#include <control/FCA.h>
#include <control/Args.h>

using namespace std;

void usage(const char *prog);
void fatal(const char *msg);
void parseArgs(int argc, char **argv);

int main(int argc, char **argv) {
  cout << "FCA with BDD" << endl << endl;

  // define precision type
  cout << fixed;

  if (argc < 2)
    usage(argv[0]);

  parseArgs(argc, argv);

  FCA *fca = new FCA( );

  try {
    fca->process( );
  } catch (IOException ioe) {
    cout << endl;
    cout << flush;

    cerr << "error: " << ioe.what( ) << endl;
    cerr << flush;
  }

  delete fca;
  delete Args::getInstance( );

  return 0;
}

void usage(const char *prog) {
  cout << "Usage: " << prog << " [Options]" << endl;
  cout << "Global options:" << endl;
  cout << "  -i   File   Burmeister input file" << endl;
  cout << "  -s   File   Output process statistics" << endl;
  cout << "  -v          Verbose" << endl;
  cout << endl;

  cout << "Concept options:" << endl;
  cout << "  -c          Enable processing concepts" << endl;
  cout << "  -h          Use a hash table to check duplicated concepts" << endl;
  cout << "  -t   Size   Hash table size" << endl;    
  cout << endl;

  cout << "Extract relations:" << endl;
  cout << "  -x          Enable extracting concepts relations" << endl;
  cout << "  -o   File   Output concept relations" << endl;
  cout << "  -w          Show concept relations on screen" << endl;
  cout << endl << flush;

  exit(1);
}

void fatal(const char *msg) {
  cout << flush;
  cerr << msg << endl << flush;

  exit(1);
}

void parseArgs(int argc, char **argv) {
  int c;
  int hashSize = 0;

  Args *a = Args::getInstance( );

  while ((c = getopt(argc, argv, "i:s:vcht:xo:w")) != -1) {
    switch (c) {
      case 'i':
        a->setInput(optarg);
        break;
      case 's':
        a->setStats(optarg);
        break;
      case 'v':
        a->setVerbose(true);
        break;
      case 'c':
        a->setConcept(true);
        break;
      case 'h':
        a->setHash(true);
        break;
      case 't':
        hashSize = atoi(optarg);
        if (hashSize <= 0)
          fatal("-t option must be a positive integer greater than zero");

        a->setHashSize(hashSize);
        break;
      case 'x':
        a->setExtract(true);
        break;
      case 'o':
        a->setOutput(optarg);
        break;
      case 'w':
        a->setShow(true);
        break;
      default:
        fatal("Invalid option");
    }
  }

  if (!a->getInput( ))
    fatal("-i option is required");
  else if (a->getHash( ) && !a->getConcept( ))
    fatal("-h option must be combined with -c option");
  else if (!a->getHash( ) && hashSize != 0)
    fatal("-t option must be combined with -h option");
  else if (a->getExtract( ) && !a->getConcept( ))
    fatal("-x option must be combined with -c option");
  else if (a->getOutput( ) && !a->getConcept( ))
    fatal("-o option must be combined with -c option");
  else if (a->getShow( ) && !a->getConcept( ))
    fatal("-w option must be combined with -c option");
  else if (a->getOutput( ) && !a->getExtract( ))
    fatal("-o option must be combined with -x option");
  else if (a->getShow( ) && !a->getExtract( ))
    fatal("-w option must be combined with -x option");
}
