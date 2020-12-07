#ifndef DNODE_H
#define DNODE_H

template <typename E>
class DNode {
private:
    E element;
    DNode<E> *next;
    DNode<E> *previous;

public:
    DNode(E element, DNode<E> *next = nullptr, DNode<E> *previous = nullptr) {
        this->element = element;
        this->next = next;
        this->previous = previous;
    }
    DNode(DNode<E> *next = nullptr, DNode<E> *previous = nullptr) {
        this->next = next;
        this->previous = previous;
    }
    E getElement() {
        return element;
    }
    void setElement(E element) {
        this->element = element;
    }
    DNode<E> *getNext() {
        return next;
    }
    void setNext(DNode<E> *next) {
        this->next = next;
    }
    DNode<E> *getPrevious() {
        return previous;
    }
    void setPrevious(DNode<E> *previous) {
        this->previous = previous;
    }
};

#endif // DNODE_H
