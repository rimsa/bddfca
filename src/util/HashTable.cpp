#include <cstdio>
#include <cstring>
#include <util/HashCode.h>
#include <util/HashTable.h>

const int HashTable::DEFAULT_HASH_SIZE = 1000000;

HashTable::HashTable( ) {
  allocateHash(DEFAULT_HASH_SIZE);
}

HashTable::HashTable(int size) {
  if (size > 0)
    allocateHash(size);
  else
    allocateHash(DEFAULT_HASH_SIZE);
}

void HashTable::allocateHash(int size) {
  int i;

  this->size = size;
  this->array = new HashNode *[size];

  for (i = 0; i < size; i++)
    array[i] = NULL;
}

HashTable::~HashTable( ) {
  int i;
  struct HashNode *tmp, *next;

  for (i = 0; i < size; i++) {
    tmp = array[i];
    while (tmp) {
      next = tmp->next;
      // delete tmp->hc; /* resource is free'd in ConceptsList
      delete tmp;
      tmp = next;
    }
  }

  delete array;
}

void HashTable::addElement(HashCode *hc) {
  int code;
  struct HashNode *node, **tmp;

  if (hc) {
    node = new HashNode;
    node->hash = hc;
    node->next = NULL;

    code = (hc->hashCode( ) & 0x7FFFFFFF) % size;
    tmp = &(array[code]);

    while (*tmp)
      tmp = &((*tmp)->next);

    *tmp = node;
  }
}

bool HashTable::existElement(HashCode *hc) {
  int code;
  struct HashNode *tmp;
  bool exist = false;

  if (hc) {
    code = (hc->hashCode( ) & 0x7FFFFFFF) % size;
    tmp = array[code];

    while (tmp && !exist) {
      if (*hc == tmp->hash)
        exist = true;

      tmp = tmp->next;
    }
  }

  return exist;
}
