#ifndef _ARGS_H
#define _ARGS_H

class Args {
  private:
    char *input;
    char *stats;
    bool verbose;

    bool concept;

    bool extract;
    char *output;
    bool show;

    bool hash;
    int hashSize;

    static Args *instance;

    Args( );
  public:
    ~Args( );

    void setInput(char *input);
    const char *getInput( );

    void setStats(char *stats);
    const char *getStats( );

    void setVerbose(bool verbose);
    bool getVerbose( );

    void setConcept(bool concept);
    bool getConcept( );

    void setExtract(bool extract);
    bool getExtract( );

    void setOutput(char *output);
    const char *getOutput( );

    void setShow(bool show);
    bool getShow( );

    void setHash(bool hash);
    bool getHash( );

    void setHashSize(int hashSize);
    int getHashSize( );

    static Args *getInstance( );
};

#endif
