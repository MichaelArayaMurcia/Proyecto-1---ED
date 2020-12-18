#ifndef TRIENODE_H
#define TRIENODE_H

#include "BSTreeDictionary.h"
#include "arraylist.h"


class TrieNode {
private:
    bool isFinal;
    int prefixCount;
    BSTreeDictionary<char, TrieNode*> children;
    ArrayList<int>* listaEnteros;

public:
    TrieNode() : children() {
        isFinal = false;
        prefixCount = 0;
        listaEnteros = new ArrayList<int>();
    }
    ~TrieNode() {}
    bool getIsFinal() {
        return isFinal;
    }
    void setIsFinal(bool isFinal) {
        this->isFinal = isFinal;
    }
    int getPrefixCount() {
        return prefixCount;
    }
    void setPrefixCount(int prefixCount) {
        this->prefixCount = prefixCount;
    }
    void increaseCount() {
        prefixCount++;
    }
    void decreaseCount() {
        prefixCount--;
    }
    bool contains(char c) {
        return children.contains(c);
    }
    void add(char c) {
        children.insert(c, new TrieNode());
    }
    void remove(char c) {
        children.remove(c);
    }
    TrieNode* getChild(char c) {
        return children.getValue(c);
    }
    List<char>* getChildren() {
        return children.getKeys();
    }
    List<TrieNode*>* getChildrenPointers() {
        return children.getValues();
    }
    void insertarnumero(int i){
        listaEnteros->insert(i);
    }
    List<int>* getListaEnteros(){
        return listaEnteros;
    }

};

#endif // TRIENODE_H
