#ifndef DEQ_H

#define DEQ_H 
#include <iostream>
using namespace std;
template <class T>

class DEQ
{
private:

    struct Node {
        T value;
        Node* next;
    };
    Node* head;

public:

    DEQ ()
    {
        head = nullptr;
    }

    ~DEQ () {
        // Traverse the DEQ and delete each node
        Node* currptr = head;
        while (currptr != nullptr) {
            Node* nextptr = currptr->next;
            delete currptr;
            currptr = nextptr;
        }
    }


    bool isEmpty () {
        return (head == nullptr);
    }

    void add_Front (T val) {
        Node* newNode = new Node;
        newNode->value = val;
        newNode->next = head;
        head = newNode;
    }

    void add_Rear (T val) {
        Node* newNode = new Node;
        newNode->value = val;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* currptr = head;
        while (currptr->next != nullptr) {
            currptr = currptr->next;
        }
        currptr->next = newNode;
    }

    void Remove_Front () {
        if (this->isEmpty ()) {
            throw("error: queue is empty");
            exit (1);
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void Remove_Back () {
        if (this->isEmpty ()) {
            throw("error: queue is empty");
            exit (1);
        }
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        Node* prevptr = nullptr;
        Node* currptr = head;
        while (currptr->next != nullptr) {
            prevptr = currptr;
            currptr = currptr->next;
        }
        prevptr->next = nullptr;
        delete currptr;
    }

    T view_Front () {
        if (this->isEmpty ()) {
            throw("error: queue is empty");
            exit (1);
        }
        return head->value;
    }

    T view_Back () {
        if (this->isEmpty ()) {
            throw("error: queue is empty");
            exit (1);
        }

        if (head->next == nullptr) {
            return head->value;
        }

        Node* currptr = head;
        while (currptr->next != nullptr) {
            currptr = currptr->next;
        }
        return currptr->value;
    }
    int Length () {
        int length = 0;
        Node* currptr = head;

        while (currptr != nullptr) {
            length++;
            currptr = currptr->next;
        }

        return length;
    }

};
#endif //DEQ_H