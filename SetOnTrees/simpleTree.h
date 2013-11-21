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

    Node* getParent(Node*);

    SimpleTree();
    SimpleTree(const TreeInterface*);
    SimpleTree (const SimpleTree &orig);
    ~SimpleTree();

    void insert(int);
    bool find(int key);
    void deleteAll();
    void print();

        SimpleTree &operator=(const SimpleTree &);
        SimpleTree operator+(const SimpleTree&);
        SimpleTree operator-(const SimpleTree&);
        SimpleTree operator^(SimpleTree&);


private:
    void insert(Node*&, int);
    bool find(Node*, int);
    void deleteAll(Node *&);
    void print(Node*,int);

    //void copyNode(Node *&, Node *);

    int &asteriscImpl(void*) ;
    void nextImpl(void*&);
    void previousImpl(void*&);
    void *beginImpl();

//////////////////////////////////////////////////////////

    void copy(const TreeInterface*);
    void copyNode(Node*&, Node*);

        void unite(Node *l, Node *&r);
        SimpleTree difference(SimpleTree&, Node*,Node*);
        void intersect(SimpleTree&, SimpleTree&, Node*);
};

#endif


