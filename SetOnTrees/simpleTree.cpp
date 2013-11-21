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

void SimpleTree::copy(const TreeInterface *orig)
{
    copyNode(root,((const SimpleTree *)orig)->root);
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
//////////////////////////////////////////////////////////////


int &SimpleTree::asteriscImpl(void *ptr)
{
    if(ptr)
        return ((Node *)ptr)->value;
    else
        throw -1;
}

SimpleTree::Node* SimpleTree::getParent(Node* ptr)
{
    if(ptr == root) return 0;

    Node *cur = root;
    while(cur->left!= ptr && cur->right!= ptr)
        cur = ptr->value < cur->value ? cur->left : cur->right;
    return cur;
}

void *SimpleTree::beginImpl()
{
    Node *cur=root;
    if(cur)
        while(cur->left)
            cur = cur->left;

    return (void*)cur;
}

void SimpleTree::nextImpl(void *&ptr)
{
    Node *cur = (Node *)ptr;
    Node *y;
    if(cur)
    {
        if(cur->right)
        {
            cur = cur->right;

            while(cur->left)
                cur = cur->left;
        }
        else
        {
            y=getParent(cur);
            while(y && cur == y->right)
            {
                cur = y;
                y=getParent(y);
            }
            if(!getParent(cur))
                cur = 0;
            else
                cur = getParent(cur);
        }

        ptr = (void *)cur;
    }
}

void SimpleTree::previousImpl(void *&ptr)
{
    Node *cur = (Node *)ptr;
    Node *y;

    if(cur)
    {
        if(cur->left)
        {
            cur = cur->left;

            while(cur->right)
                cur = cur->right;

            ptr = (void *)cur;
        }
        else
        {
            y=getParent(cur);
            while(y && cur == y->left)
            {
                cur = y;
                y=getParent(y);
            }

            if(getParent(cur))
                ptr = (void *)getParent(cur);
            else
                return;
        }
    }
    else
    {
        cur = root;
        if(cur)
            while(cur->right)
                cur = cur->right;
        ptr = (void*)cur;
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

