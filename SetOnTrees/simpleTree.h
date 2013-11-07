#ifndef SIMPLETREE_H
#define SIMPLETREE_H

#include "nvi.h"

class SimpleTree: public TreeInterface
{

protected:
struct Node
    {
        int value;
        Node *left;
        Node *right;

        Node(int val)
        {
            value=val;
            left=right=0;
        }
    };
    Node *root;
public:

    SimpleTree();
    ~SimpleTree();

    void insert(int);
    bool find(int key);
    void deleteAll();
    void print();

    SimpleTree (const SimpleTree &);
    void copyNode(Node *&, Node *);

    SimpleTree &operator=(const SimpleTree &);
    SimpleTree operator+(const SimpleTree&);
    SimpleTree operator-(const SimpleTree&);
    SimpleTree operator^(SimpleTree&);

private:
    void insert(Node*&, int);
    bool find(Node*, int);
    void deleteAll(Node *&);
    void print(Node*,int);

    void unite(Node *l, Node *&r);
    SimpleTree difference(SimpleTree&, Node*,Node*);
    void intersect(SimpleTree&, SimpleTree&, Node*);

};

#endif


