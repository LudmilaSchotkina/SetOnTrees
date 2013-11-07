#ifndef NVI_H
#define NVI_H

struct Node;

class TreeInterface //NVI
{
public:

    void insertTreap(Node*&, Node*);

    void insertTree(Node*&, int);  //For SimpleTree

private:
    virtual void insert(int)=0;
};














/*
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
    class Iterator;
    Treap();
    ~Treap();
    Treap (const Treap &);
    void copyNode(Node *&, Node *);
    Treap &operator=(const Treap &);
    void deleteAll(Node *&);

    void insert(int);
    void insert(Node*&, Node*);

    int find(int key);
    int find(Node*, int);
    Node *search(Node *t, int key);

    void merge (Node *left,Node *right);
    void merge (Node *&, Node *,Node *);
    void split (Node *, int, Node *&, Node *&);

    void print(Node*,int);

    void unite(Node *&l, Node *&r);
    Treap difference(Treap&, Node*,Node*);
    void intersect(Treap&, Treap&, Node*);

};


///////////////////////////////////////
class Treap::Iterator
{
public:
    //friend Treap;
    Iterator();
    Iterator(Node *node);
    ~Iterator();

    Iterator operator++();
    int &operator*() const;

private:
    Node *cur;
};

*/

#endif
