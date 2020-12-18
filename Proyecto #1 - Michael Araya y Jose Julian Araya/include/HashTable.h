#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "Dictionary.h"
#include "KVPair.h"
#include "LinkedList.h"
#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

using namespace std;

template <typename K, typename V>
class HashTable : public Dictionary<K, V> {
private:
    LinkedList<KVPair<K, V> > *buckets;
    int nbuckets;
    int size;

    int h(K key) {
        return compress(hashCodePolynomial(key));
    }
    // Genera un código hash polinomial con constante de 33
    template <typename T>
    int hashCodePolynomial(T key) {
        int a = 33;
        int result = 0;
        char* bytes = reinterpret_cast<char*>(&key);
        for (unsigned int i = 0; i < sizeof(K); i++) {
            result += bytes[i] * pow(a, i);
        }
        return result;
    }
    int hashCodePolynomial(string key) {
        int a = 33;
        int result = 0;
        for (unsigned int i = 0; i < key.length(); i++) {
            result += key[i] * pow(a, i);
        }
        return result;
    }
    // Función de compresión por multiplicación, suma y división
    int compress(int hashCode) {
        int a = 1097;
        int b = 1279;
        return abs(a * hashCode + b) % nbuckets;
    }
    // Método auxiliar que verifica que una llave no exista.
    // Si se encuentra la llave, lanza exepción.
    // La posición actual de la lista queda señalando al final
    // de la lista.
    void checkNotExisting(K key) throw (runtime_error) {
        if (buckets[h(key)].contains(key))
            throw runtime_error("Duplicated key.");
    }
    // Método auxiliar que verifica que una llave sí exista.
    // Si no se encuentra la llave, lanza excepción
    // La posición actual de la lista queda señalando al
    // elemento buscado.
    void checkExisting(K key) throw (runtime_error) {
        if (!buckets[h(key)].contains(key)) {
            throw runtime_error("Key not found.");
        }
    }

public:
    HashTable(int nbuckets = 1021) {
        buckets = new LinkedList<KVPair<K, V> >[nbuckets];
        this->nbuckets = nbuckets;
        size = 0;
    }
    ~HashTable() {
        delete [] buckets;
    }
    void insert(K key, V value) {
        checkNotExisting(key);
        KVPair<K, V> p(key, value);
        buckets[h(key)].append(p);
        size++;
    }
    V remove(K key) {
        checkExisting(key);
        KVPair<K, V> p(key);
        p = buckets[h(key)].remove();
        size--;
        return p.getValue();
    }
    V getValue(K key) {
        checkExisting(key);
        KVPair<K, V> p = buckets[h(key)].getElement();
        return p.getValue();
    }
    void setValue(K key, V value) {
        checkExisting(key);
        buckets[h(key)].remove();
        KVPair<K, V> p(key, value);
        buckets[h(key)].append(p);
    }
    void clear() {
        for (int i = 0; i < nbuckets; i++) {
            buckets[i].clear();
        }
    }
    bool contains(K key) {
        KVPair<K, V> p(key);
        return buckets[h(key)].contains(p);
    }
    List<K>* getKeys() {
        List<K> *keys = new LinkedList<K>();
        for(int i = 0; i < nbuckets; i++){
            for(buckets[i].goToStart(); !buckets[i].atEnd(); buckets[i].next()){
                KVPair<K,V> temp = buckets[i].getElement();
                keys->append(temp.getKey());
            }
        }
        return keys;
    }
    List<V>* getValues() {
        List<V> *values = new LinkedList<V>();
        List<K> *keys = getKeys();
        for(keys->goToStart(); !keys->atEnd(); keys->next()){
            values->append(getValue(keys->getElement()));
        }
        return values;
    }
    int getSize() {
        return size;
    }
    void update(Dictionary<K,V> *Dict) {
        List<K> *keys = Dict->getKeys();
        for(keys->goToStart(); !keys->atEnd(); keys->next()){
            if(!contains(keys->getElement())){
                insert(keys->getElement(), Dict->getValue(keys->getElement()));
            }
            else{
                setValue(keys->getElement(), Dict->getValue(keys->getElement()));
            }
        }
    }
    void zip(List<K> *keys, List<V> *values) {
        if(keys->getSize() > values->getSize()){
            keys->goToStart();
            for(values->goToStart(); !values->atEnd(); values->next()){
                insert(keys->getElement(), values->getElement());
                keys->next();
            }
        }
        else{
            values->goToStart();
            for(keys->goToStart(); !keys->atEnd(); keys->next()){
                insert(keys->getElement(), values->getElement());
                values->next();
            }
        }
    }
};

#endif // HASHTABLE_H
