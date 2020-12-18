#ifndef SORTEDARRAYDICTIONARY_H
#define SORTEDARRAYDICTIONARY_H
#include "Dictionary.h"
#include "SortedArrayList.h"
#include "DLinkedList.h"
#include "KVPair.h"
#include <stdexcept>

using std::runtime_error;

template <typename K, typename V>
class SortedArrayDictionary : public Dictionary<K, V> {
private:
    SortedArrayList<KVPair<K, V> > pairs;

    void checkNotExisting(K key) {
        if (contains(key)) {
            throw runtime_error("Duplicated key.");
        }
    }
    void checkExisting(K key) {
        if (!contains(key)) {
            throw runtime_error("Key not found.");
        }
    }

public:
    SortedArrayDictionary(int max = DEFAULT_MAX_SIZE) : pairs(max) {}
    void insert(K key, V value) {
        checkNotExisting(key);
        KVPair<K, V> p(key, value);
        pairs.append(p);
    }
    V remove(K key) {
        checkExisting(key);
        KVPair<K, V> p = pairs.remove();
        return p.getValue();
    }
    V getValue(K key) {
        checkExisting(key);
        KVPair<K, V> p = pairs.getElement();
        return p.getValue();
    }
    void setValue(K key, V value) {
        checkExisting(key);
        pairs.remove();
        KVPair<K, V> p(key, value);
        pairs.append(p);
    }
    bool contains(K key) {
        KVPair<K, V> p(key);
        return pairs.contains(p);
    }
    List<K>* getKeys() {
        List<K> *keys = new DLinkedList<K>();
        for (pairs.goToStart(); !pairs.atEnd(); pairs.next()) {
            KVPair<K, V> p = pairs.getElement();
            keys->append(p.getKey());
        }
        return keys;
    }
    List<V>* getValues() {
        List<V> *values = new DLinkedList<V>();
        for (pairs.goToStart(); !pairs.atEnd(); pairs.next()) {
            KVPair<K, V> p = pairs.getElement();
            values->append(p.getValue());
        }
        return values;
    }
    int getSize() {
        return pairs.getSize();
    }
};

#endif // SORTEDARRAYDICTIONARY_H
