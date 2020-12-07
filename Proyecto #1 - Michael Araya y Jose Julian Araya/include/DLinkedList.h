#ifndef DLINKEDLIST_H
#define DLINKEDLIST_H

#include "List.h"
#include "DNode.h"
#include <stdexcept>

using std::runtime_error;

template <typename E>
class DLinkedList : public List<E> {
private:
    DNode<E> *head;
    DNode<E> *current;
    DNode<E> *tail;
    int size;

public:
    DLinkedList() {
        current = head = new DNode<E>();
        tail = new DNode<E>(nullptr, head);
        head->setNext(tail);
        size = 0;
    }
    ~DLinkedList() {
        clear();
        delete head;
        delete tail;
    }
    void insert(E element) {
        DNode<E> *newNode = new DNode<E>(element, current->getNext(), current);
        current->getNext()->setPrevious(newNode);
        current->setNext(newNode);
        size++;
    }
    void append(E element) {
        DNode<E> *newNode = new DNode<E>(element, tail, tail->getPrevious());
        tail->getPrevious()->setNext(newNode);
        tail->setPrevious(newNode);
        size++;
    }
    E remove() {
        if (size == 0)
            throw runtime_error("List is empty");
        if (current->getNext() == tail)
            throw runtime_error("No current element.");
        E result = current->getNext()->getElement();
        current->setNext(current->getNext()->getNext());
        delete current->getNext()->getPrevious();
        current->getNext()->setPrevious(current);
        size--;
        return result;
    }
    void clear() {
        current = head->getNext();
        while (current != tail) {
            head->setNext(current->getNext());
            delete current;
            current = head->getNext();
        }
        tail->setPrevious(head);
        current = head;
        size = 0;
    }
    E getElement() {
        if (size == 0)
            throw runtime_error("List is empty");
        if (current->getNext() == tail)
            throw runtime_error("No current element.");
        return current->getNext()->getElement();
    }
    void goToStart() {
        current = head;
    }
    void goToEnd() {
        current = tail->getPrevious();
    }
    void goToPos(int pos) {
        if (pos < 0 || pos > size)
            throw runtime_error("Index out of range.");
        current = head;
        for (int i = 0; i < pos; i++) {
            current = current->getNext();
        }
    }
    void next() {
        if (current->getNext() != tail) {
            current = current->getNext();
        }
    }
    void previous() {
        if (current != head) {
            current = current->getPrevious();
        }
    }
    bool atStart() {
        return current == head;
    }
    bool atEnd() {
        return current == tail->getPrevious();
    }
    int getPos() {
        int pos = 0;
        DNode<E> *temp = head;
        while (temp != current) {
            pos++;
            temp = temp->getNext();
        }
        return pos;
    }
    int getSize() {
        return size;
    }
};

#endif // DLINKEDLIST_H
