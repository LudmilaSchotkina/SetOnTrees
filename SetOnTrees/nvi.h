#ifndef NVI_H
#define NVI_H

struct Node;
class Iterator;

class TreeInterface //NVI
{
public:
    friend class Iterator;

    TreeInterface() {}
    TreeInterface(const TreeInterface &orig);
    ~TreeInterface();

    void insertElement(int);
    bool findElement(int);
    void removeAll();

    Iterator begin();
    Iterator end();

private:
    virtual void insert(int) = 0;
    virtual bool find(int) = 0;
    virtual void deleteAll() {};

    virtual void copy(const TreeInterface*) {}

    int &asterisc(void*);
    void next(void*&);
    void previous(void*&);

    virtual int &asteriscImpl(void*) = 0;
    virtual void nextImpl(void*&) = 0;
    virtual void previousImpl(void*&) = 0;

    virtual void *beginImpl() = 0;
    // virtual void *endImpl() = 0;

};

class Iterator
{
public:
    friend class TreeInterface;

    Iterator();
    ~Iterator();

    int &operator*();
    Iterator operator++();
    Iterator operator++(int);

    Iterator operator--();
    Iterator operator--(int);

    bool operator==(const Iterator&);
    bool operator!=(const Iterator&);

    Iterator (TreeInterface*, void*);

private:
    TreeInterface *owner;
    void *cur;

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
