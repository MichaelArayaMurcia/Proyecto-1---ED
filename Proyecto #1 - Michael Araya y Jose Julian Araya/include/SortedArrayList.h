#ifndef SORTEDARRAYLIST_H
#define SORTEDARRAYLIST_H

#include "arraylist.h"

template <typename E>
class SortedArrayList : public ArrayList<E> {
public:
    SortedArrayList(int max) : ArrayList<E>(max) {}
    void insert(E element) {
        ArrayList<E>::goToStart();
        while (!ArrayList<E>::atEnd() && element >= ArrayList<E>::getElement()) {
            ArrayList<E>::next();
        }
        ArrayList<E>::insert(element);
    }
    void append(E element) {
        insert(element);
    }
    int indexOf(E element) {
        int min = 0;
        int max = ArrayList<E>::size - 1;
        while (min <= max) {
            int mid = (min + max) / 2;
            if (element == ArrayList<E>::elements[mid]) {
                return mid;
            } else if (element < ArrayList<E>::elements[mid]) {
                max = mid - 1;
            } else {
                min = mid + 1;
            }
        }
        return -1;
    }
    bool contains(E element) {
        int pos = indexOf(element);
        if (pos != -1) ArrayList<E>::goToPos(pos);
        return pos != -1;
    }
};

#endif // SORTEDARRAYLIST_H
