#include <iostream>
#include <cstdlib>
#include "treap.h"

using namespace std;

Treap::Treap():
    root(0) {}

Treap::Treap (const Treap &orig)
{
    if (orig.root)
    {
        root=new Node(orig.root->value, orig.root->priority, orig.root->counter);
        copyNode(root, orig.root);
    }
    else root=0;
}

Treap::~Treap ()
{
    deleteAll();
}

void Treap::deleteAll()
{
    deleteAll(root);
}

void Treap::print()
{
    print(root,0);
}
bool Treap::find(int key)
{
    return find(root, key);
}
void Treap::insert(int val)
{
    insert(root, new Node(val, rand()%1000+1, 1));
}
void Treap::deleteAll(Node *&ptr)
{
    if(ptr)
    {
        deleteAll(ptr->left);
        deleteAll(ptr->right);
        delete ptr;
    }
}

////////////////////////////////////////////////////

Treap &Treap::operator=(const Treap &orig)
{
    if(this==&orig)
        return *this;
    deleteAll(root);
    copyNode(root,orig.root);
    return *this;
}

Treap Treap::operator+(const Treap &orig)
{
    Treap tmp=orig;
    unite(root, tmp.root);
    return *this;
}

Treap Treap::operator-(const Treap &orig)
{
    Treap temp;
    if(!this && orig.root)
    {
        deleteAll(temp.root);
        *this=temp;
    }
    else  if(this && !orig.root)
        return *this;
    if(this!=&orig)
    {
        difference(temp,root,orig.root);
        return temp;
    }
    else
        return *this;
}

Treap Treap::operator^(Treap &orig)
{
    Treap temp;
    intersect(temp, orig, root);
    return temp;
}




////////////////////////////////////////////////
////////////////FUNCTIONS UTILITIES/////////////
////////////////////////////////////////////////

void Treap::copyNode(Node *&newNode, Node *orig)
{
    if(orig==0)
        newNode = 0;

    if (orig)
    {
        newNode=new Node(orig->value,orig->priority, orig->counter);
        if(orig->left)
            copyNode(newNode->left,orig->left);
        else
            newNode->left =0;

        if(orig->right)
            copyNode(newNode->right,orig->right);
        else
            newNode->right =0;
    }
}

void Treap::print(Node *ptr,int element)
{
    while (ptr)
    {
        print(ptr->right, element+5);

        for (int i=1; i<element; ++i)
            cout << ' ';

        cout << ptr->value<<","<<ptr->priority<<","<<ptr->counter<<endl;
        ptr = ptr->left;
        element += 5;
    }

}

bool Treap::find(Node *ptr, int value)
{
    while (ptr){
    if (ptr->value > value)
         ptr=ptr->left;
    else if (ptr->value < value)
        ptr=ptr->right;
    else return true;
    }
    return false;
}
Node *Treap::search(Node *t, int value)
{
    while(t)
    {
        if (t->value > value)
            t=t->left;
        else if (t->value < value)
            t=t->right;
        else return t;
    }
    return 0;
}

void Treap::insert(Node *&ptr, Node *val)
{
    Node *newNode;
    newNode= new Node(val->value,val->priority,val->counter);

    if(!find(root,val->value))
    {
        if (ptr==0)
            ptr=val;
        else if (val->priority > ptr->priority)
        {
            split(ptr,val->value,val->left, val->right);
            ptr=val;
        }
        else if (val->value > ptr->value)
            insert(ptr->right,val);

        else if (val->value < ptr->value)
            insert(ptr->left,val);
    }
    else if(find(ptr,val->value))
    {
        newNode=search(ptr,val->value);
        newNode->counter=newNode->counter+val->counter;
    }
}

void Treap::split (Node *ptr, int value, Node *&left, Node *&right)
{
    if (!ptr)
        left=right=NULL;

    else if (value > ptr->value)
    {
        split (ptr->right, value, ptr->right, right);
        left=ptr;
    }
    else
    {
        split(ptr->left,value,left,ptr->left);
        right=ptr;
    }
}

//////////////////////////////////////////////////////
void Treap::unite(Node *l, Node *r)
{
    if(r)
    {
        insert(l, new Node(r->value, r->priority,r->counter));
        unite(l,r->left);
        unite(l,r->right);
    }
}

Treap Treap::difference(Treap &ptr, Node *a,Node *b)
{
    Node *newNode;

    if(a)
    {
        if(!find(b, a->value))
            ptr.insert(ptr.root, new Node(a->value, a->priority,a->counter));
        else  if(find(b, a->value))
        {
            newNode= new Node(b->value,b->priority,b->counter);
            newNode=search(b,a->value);
            a->counter= a->counter-b->counter;
            ptr.insert(ptr.root, new Node(a->value, a->priority,a->counter));
        }
        difference(ptr, a->left, b);
        difference(ptr, a->right, b);

    }
    return ptr;
}

void Treap::intersect(Treap &a, Treap &b, Node *ptr)
{
    if(!ptr) return;

    if(b.find(ptr->value))
        a.insert(ptr->value);
    intersect(a,b,ptr->left);
    intersect(a,b,ptr->right);
}

/*
void Treap::merge (Node *left,Node *right)
{
    merge (root, left,right);
}
void Treap::merge (Node *&ptr, Node *left,Node *right)
{
    if (!left || !right)
        ptr = left ? left : right;
    else if (left->priority > right->priority)
    {
        merge (left->right, left->right, right);
        ptr = left;
    }
    else
    {
        merge (right->left, left, right->left);
        ptr = right;
    }
}

*/


