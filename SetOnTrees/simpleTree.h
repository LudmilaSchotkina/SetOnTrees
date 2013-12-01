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
    bool find(int);
    void remove(int);
    void removeAll();
    void print();

private:
    void insert(Node*&, int);
    bool find(Node*, int);
    void remove(Node*, int);
    void removeAll(Node *&);
    void print(Node*,int);


    int &asteriscImpl(void*) ;
    void nextImpl(void*&);
    void previousImpl(void*&);
    void *beginImpl();


    void copy(const TreeInterface*);
    void copyNode(Node*&, Node*);

};


#endif
