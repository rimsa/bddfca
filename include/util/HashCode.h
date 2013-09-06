#ifndef _HASH_CODE_H
#define _HASH_CODE_H

class HashCode {
  public:
    virtual ~HashCode() {}
    virtual int hashCode( ) = 0;
    virtual int operator==(const HashCode *code) = 0;
};

#endif
