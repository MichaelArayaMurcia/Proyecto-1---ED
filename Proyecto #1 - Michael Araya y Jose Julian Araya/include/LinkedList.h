#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include <stdexcept>
#include <iostream>

using std::runtime_error;
using std::cout;
using std::endl;

template <typename E>
class LinkedList : public List<E> {
private:
    Node<E>* head;
    Node<E>* tail;
    Node<E>* current;
    int size;

public:
    LinkedList() {
        head = tail = current = new Node<E>();
        size = 0;
    }
    ~LinkedList() {
        clear();
        delete head;
    }
    void insert(E element) {
        current->next = new Node<E>(element, current->next);
        if (current == tail) {
            tail = tail->next;
        }
        size++;
    }
    void append(E element) {
        tail->next = new Node<E>(element);
        tail = tail->next;
        size++;
    }
    E remove() throw(runtime_error) {
        if (current->next == nullptr) {
            throw runtime_error("No element to remove.");
        }
        E result = current->next->element;
        Node<E> *temp = current->next;
        current->next = current->next->next;
        if (current->next == nullptr) {
            tail = current;
        }
        delete temp;
        size--;
        return result;
    }
    void clear() {
        current = head;
        while (head != nullptr) {
            head = head->next;
            delete current;
            current = head;
        }
        head = tail = current = new Node<E>();
        size = 0;
    }
    E getElement() throw(runtime_error) {
        if (current->next == nullptr) {
            throw runtime_error("No element to get.");
        }
        return current->next->element;
    }
    void goToStart() {
        current = head;
    }
    void goToEnd() {
        current = tail;
    }
    void goToPos(int newPos) throw(runtime_error) {
        if ((newPos < 0) || (newPos > size)) {
            throw runtime_error("Index out of bounds");
        }
        current = head;
        for (int i = 0; i < newPos; i++) {
            current = current->next;
        }
    }
    void previous() {
        if (current != head) {
            Node<E> *temp = head;
            while (temp->next != current) {
                temp = temp->next;
            }
            current = temp;
        }
    }
    bool atStart() {
        return current == head;
    }
    void next() {
        if (current != tail) {
            current = current->next;
        }
    }
    bool atEnd() {
        return current == tail;
    }
    int getPos() {
        int pos = 0;
        Node<E>* temp = head;
        while (temp != current) {
            pos++;
            temp = temp->next;
        }
        return pos;
    }
    int getSize() {
        return size;
    }
    bool contains(E element) {
        for (goToStart(); !atEnd(); next()) {
            if (getElement() == element) {
                return true;
            }
        }
        return false;
    }
    int indexOf(E element) {
        if (contains(element)) {
            return getPos();
        }
        return -1;
    }
    void extend(List<E> &L) {
        int pos = L.getPos();
        for (L.goToStart(); !L.atEnd(); L.next())
            append(L.getElement());
        L.goToPos(pos);
    }
    void sort() {
        if (size <= 1) {
            return;
        }
        LinkedList<E> low;
        LinkedList<E> high;

        goToStart();
        E pivot = remove();
        while (size > 0) {
            E element = remove();
            if (element < pivot) {
                low.append(element);
            } else {
                high.append(element);
            }
        }

        low.sort();
        high.sort();

        low.goToStart();
        while (low.getSize() > 0) {
            append(low.remove());
        }
        append(pivot);

        high.goToStart();
        while (high.getSize() > 0) {
            append(high.remove());
        }
    }
    void print() {
        Node<E> *currentBkp = current;
        for (goToStart(); getPos() < size; next()) {
            cout << getElement() << " ";
        }
        cout << endl;
        current = currentBkp;
    }
};


#endif // LINKEDLIST_H
