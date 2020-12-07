#ifndef KVPAIR_H
#define KVPAIR_H

template <typename K, typename V>
class KVPair {
private:
    K key;
    V value;

public:
    KVPair() {}
    KVPair(K key) {
        this->key = key;
    }
    KVPair(K key, V value) {
        this->key = key;
        this->value = value;
    }
    K getKey() {
        return key;
    }
    void setKey(K key) {
        this->key = key;
    }
    V getValue() {
        return value;
    }
    void setValue(V value) {
        this->value = value;
    }
    void operator= (const KVPair &obj) {
        key = obj.key;
        value = obj.value;
    }
    bool operator== (const KVPair &obj) {
        return key == obj.key;
    }
    bool operator!= (const KVPair &obj) {
        return key != obj.key;
    }
    bool operator< (const KVPair &obj) {
        return key < obj.key;
    }
    bool operator<= (const KVPair &obj) {
        return key <= obj.key;
    }
    bool operator> (const KVPair &obj) {
        return key > obj.key;
    }
    bool operator>= (const KVPair &obj) {
        return key >= obj.key;
    }
};

#endif // KVPAIR_H
