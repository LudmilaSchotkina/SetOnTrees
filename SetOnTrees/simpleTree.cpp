#include "simpleTree.h"
#include <iostream>

using namespace std;

SimpleTree::SimpleTree():
    root(0) {}

SimpleTree::SimpleTree (const SimpleTree &original)
{
    if (original.root)
    {
        root=new Node(original.root->value);
        copyNode(root, original.root);
    }
    else root=0;
}

SimpleTree::~SimpleTree ()
{
    deleteAll();
}

void SimpleTree::deleteAll()
{
    deleteAll(root);
}


void SimpleTree::print()
{
    print(root,0);
}
bool SimpleTree::find(int key)
{
    return find(root, key);
}
void SimpleTree::insert(int val)
{
    insert(root, val);
}
void SimpleTree::deleteAll(Node *&ptr)
{
    if(ptr)
    {
        deleteAll(ptr->left);
        deleteAll(ptr->right);
        delete ptr;
    }
}

///////////////////////////////////////////////////////////

SimpleTree &SimpleTree::operator=(const SimpleTree &original)
{
    if(this==&original)
        return *this;
    deleteAll(root);
    copyNode(root,original.root);
    return *this;
}

SimpleTree SimpleTree::operator+(const SimpleTree &orig)
{
    if(this!= &orig)
    {
        SimpleTree tmp=orig;
        unite(root, tmp.root);
        return tmp;
    }
    return *this;
}

SimpleTree SimpleTree::operator-(const SimpleTree &orig)
{
    SimpleTree temp;
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

SimpleTree SimpleTree::operator^(SimpleTree &orig)
{
    SimpleTree temp;
    intersect(temp, orig, root);
    return temp;
}


////////////////////////////////////////////////
////////////////FUNCTIONS UTILITIES/////////////
////////////////////////////////////////////////
void SimpleTree::copyNode(Node *&newNode, Node *original)
{
    if(original==0)
        newNode = 0;

    if (original)
    {
        newNode=new Node(original->value);
        if(original->left)
            copyNode(newNode->left,original->left);
        else
            newNode->left =0;

        if(original->right)
            copyNode(newNode->right,original->right);
        else
            newNode->right =0;
    }
}
void SimpleTree::print(Node *ptr,int element)
{
    while (ptr)
    {
        print(ptr->right, element+2);

        for (int i=1; i<element; ++i)
            cout << ' ';

        cout << ptr->value<<endl;
        ptr = ptr->left;
        element += 2;
    }

}

bool SimpleTree::find(Node *ptr, int value)
{
    while (ptr)
    {
        if (ptr->value > value)
            ptr=ptr->left;
        else if (ptr->value < value)
            ptr=ptr->right;
        else return true;
    }
    return false;

}

void SimpleTree::insert(Node *&ptr, int val)
{
    if (ptr==0)
        ptr=new Node(val);
    else if (val < ptr->value)
        insert(ptr->left,val);

    else if (val > ptr->value)
        insert(ptr->right,val);

}

////////////////////////////////////////////////////////

void SimpleTree::unite(Node *l, Node *&r)
{
    if(l)
    {
        insert(r, l->value);
        if(l->right)
            unite(l->right,r);
        if(l->left)
            unite(l->left,r);
    }
}

SimpleTree SimpleTree::difference(SimpleTree &ptr, Node *a,Node *b)
{
    if(a)
    {
        if(!find(b, a->value))
            ptr.insert(ptr.root, a->value);

        difference(ptr, a->left, b);
        difference(ptr, a->right, b);
    }
    return ptr;
}

void SimpleTree::intersect(SimpleTree &a, SimpleTree &b, Node *ptr)
{
    if(!ptr) return;
    if(b.find(ptr->value))
        a.insert(ptr->value);
    intersect(a,b,ptr->left);
    intersect(a,b,ptr->right);
}

