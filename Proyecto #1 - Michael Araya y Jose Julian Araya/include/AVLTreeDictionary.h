#ifndef AVLTREEDICTIONARY_H
#define AVLTREEDICTIONARY_H
#include <iostream>

#include "Dictionary.h"
#include "KVPair.h"
#include <stdexcept>
#include "AVLTree.h"

#define DEFAULT_MAX_SIZE 1024

template <typename K, typename V>
class AVLTreeDictionary : public Dictionary<K, V>
{
    protected:

    private:

    AVLTree<KVPair<K, V>> pairs;
    int size = 0;

    public:
        //1. ------------ Constructor -------------
        AVLTreeDictionary() {}
        //BSTreeDictionary(int max = DEFAULT_MAX_SIZE) : pairs(max) {}

        //1. ------------ Destructor --------------
        ~AVLTreeDictionary() {}

        //2. ------------ insert ------------------
        void insert(K key, V value){
            if(contains(key)){
                throw runtime_error("Key already exists.");
            }
            KVPair<K, V> p(key, value);
            pairs.insert(p);
        }

        //3. ------------ remove ------------------
        V remove(K key){
            //KVPair<K, V> p = pairs.remove();
            if(!contains(key)){
                    throw runtime_error("Key not found.");
            }
            KVPair<K, V> p = pairs.find(key);
            KVPair<K, V> p2 = pairs.remove(p);
            return p2.getValue();
        }

        //4. ------------ getValue ----------------
        V getValue(K key){
            if(!contains(key)){
                throw runtime_error("Key not found.");
            }
            KVPair<K, V> p = pairs.find(key);
            return p.getValue();
        }

        //5. ------------ setValue ----------------
        void setValue(K key, V value){
            if(!contains(key)){
                    throw runtime_error("Key not found.");
            }
            KVPair<K,V> temp2 = pairs.remove(KVPair<K,V>(key));
            temp2.setValue(value);
            pairs.insert(temp2);
        }

        //6. ------------ contains ----------------
        bool contains(K key){
            KVPair<K, V> p(key);
            return pairs.contains(p);
        }

        //7. ------------ clear -------------------
        void clear(){
            pairs.clear();
        }

        //8. ------------ getKeys -----------------
        List<K>* getKeys(){
            List<K>* llaves = new DLinkedList<K>();
            List<KVPair<K, V>>* elementos = pairs.getElements();

                for(elementos->goToStart(); !elementos->atEnd(); elementos->next()){
                    KVPair<K,V> elemento = elementos->getElement();
                    K llave = elemento.getKey();
                    llaves->insert(llave);
                }

            return llaves;

            }

        //9. ------------ getValues ---------------
        List<V>* getValues(){
            List<V> * valores = new DLinkedList<V>();
            List<KVPair<K, V>>* elementos = pairs.getElements();

                for(elementos->goToStart(); !elementos->atEnd(); elementos->next()){
                    KVPair<K,V> elemento = elementos->getElement();
                    V valor = elemento.getValue();
                    valores->insert(valor);
                }

            return valores;

        }

        //10. ------------ getSize ----------------
        int getSize(){
            return pairs.getSize();
        }

        //11. ------------ update -----------------
        void update(Dictionary<K,V> *D){
            List<K>* llaves = D->getKeys();

            for(llaves->goToStart(); !llaves->atEnd(); llaves->next()){
                std::cout << "El update \n";

                K llave = llaves->getElement();
                if(contains(llave)){
                    setValue(llave, D->getValue(llave));
                }
                else{
                    insert(llave, D->getValue(llave));
                }
            }
        }

        //12. ------------ zip --------------------
        void zip(List<K> *keys, List<V>* values){
            for(keys->goToStart(); !keys->atEnd(); keys->next()){
                K key = keys->getElement();
                V value = values->getElement();
                KVPair<K, V> p(key, value);
                insert(key, value);
                values->next();
            }
        }


};
#endif // AVLTREEDICTIONARY_H
