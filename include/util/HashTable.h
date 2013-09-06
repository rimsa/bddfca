#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <util/HashCode.h>

struct HashNode {
  HashCode *hash;
  struct HashNode *next;
};

class HashTable {
  private:
    int size;
    HashNode **array;

    void allocateHash(int size);
  public:
    static const int DEFAULT_HASH_SIZE;

    HashTable( );
    HashTable(int size);
    ~HashTable( );

    void addElement(HashCode *hc);
    bool existElement(HashCode *hc);
};

#endif
