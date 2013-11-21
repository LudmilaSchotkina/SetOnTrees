#ifndef TREAP_H
#define TREAP_H

#include "nvi.h"

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
class Treap: public TreeInterface
{
public:
    Treap();
    Treap (const Treap &);
    ~Treap();

    void insert(int);
    bool find(int key);
    void deleteAll();
    void print();

    //void merge (Node *left,Node *right);
    void copyNode(Node *&, Node *);
    /*
        Treap &operator=(const Treap &);
        Treap operator+(const Treap&);
        Treap operator-(const Treap&);
        Treap operator^(Treap&);
    */
protected:
    Node *root;

private:
    void insert(Node*&, Node*);
    bool find(Node*, int);
    void deleteAll(Node *&);
    void print(Node*,int);

    void split (Node *, int, Node *&, Node *&);
    void merge (Node *&, Node *,Node *);
    Node *search(Node *t, int key);
    /*
        void unite(Node*, Node*);
        Treap difference(Treap&, Node*,Node*);
        void intersect(Treap&, Treap&, Node*);
    */
};

#endif


