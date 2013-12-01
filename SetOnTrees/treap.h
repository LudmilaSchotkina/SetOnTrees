#ifndef TREAP_H
#define TREAP_H

#include "nvi.h"


class Treap: public TreeInterface
{
protected:
struct Node
{
    int value;
    Node *left;
    Node *right;
    int priority;
    int counter;

    Node(int val,int prior,int cnt):value(val)
    {
        priority=prior;
        left=right=0;
        counter=cnt;
    }
};
    Node *root;
public:
    Treap();
    Treap (const Treap &);
    ~Treap();

    void insert(int);
    bool find(int key);
    void remove(int);
    void removeAll();
    void print();

private:
    void insert(Node*&, Node*);
    bool find(Node*, int);
    void remove(Node*, int);
    void removeAll(Node *&);
    void print(Node*,int);

    int &asteriscImpl(void*) ;
    void nextImpl(void*&);
    void previousImpl(void*&);
    void *beginImpl();



    void copy(const TreeInterface*);
    void copyNode(Node *&, Node *);

    Node* getParent(Node*);
    void split (Node *, int, Node *&, Node *&);
    void merge (Node *&, Node *,Node *);
    Node *search(Node *t, int key);

};

#endif


