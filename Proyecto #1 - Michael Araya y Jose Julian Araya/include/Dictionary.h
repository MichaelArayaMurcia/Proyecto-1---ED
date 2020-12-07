#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "list.h"

template <typename K, typename V>
class Dictionary {
public:
    Dictionary() {}
    virtual ~Dictionary() {}
    virtual void insert(K key, V value) = 0;
    virtual V remove(K key) = 0;
    virtual V getValue(K key) = 0;
    virtual void setValue(K key, V value) = 0;
    virtual void clear() = 0;
    virtual bool contains(K key) = 0;
    virtual List<K>* getKeys() = 0;
    virtual List<V>* getValues() = 0;
    virtual int getSize() = 0;
};

#endif // DICTIONARY_H

