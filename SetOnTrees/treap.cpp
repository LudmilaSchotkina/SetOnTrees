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
    removeAll();
}

void Treap::insert(int val)
{
    insert(root, new Node(val, rand()%1000+1, 1));
}
bool Treap::find(int key)
{
    return find(root, key);
}
void Treap::remove(int val)
{
    remove(root, val);
}
void Treap::removeAll()
{
    removeAll(root);
}
void Treap::removeAll(Node *&ptr)
{
    if(ptr)
    {
        removeAll(ptr->left);
        removeAll(ptr->right);
        delete ptr;
    }
}
void Treap::print()
{
    print(root,0);
}

void Treap::copy(const TreeInterface *orig)
{
    copyNode(root,((const Treap*)orig)->root);
}
////////////////////////////////////////////////////

int &Treap::asteriscImpl(void *ptr)
{
    if(ptr)
        return ((Node *)ptr)->value;
    else
        throw -1;
}

Treap::Node* Treap::getParent(Node* ptr)
{
    if(ptr == root) return 0;

    Node *cur = root;
    while(cur->left!= ptr && cur->right!= ptr)
        cur = ptr->value < cur->value ? cur->left : cur->right;
    return cur;
}

void *Treap::beginImpl()
{
    Node *cur=root;
    if(cur)
        while(cur->left)
            cur = cur->left;

    return (void*)cur;
}

void Treap::nextImpl(void *&ptr)
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

void Treap::previousImpl(void *&ptr)
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

void Treap::insert(Node *&ptr, Node *val)
{
    Node *newNode;
    newNode= new Node(val->value,val->priority,val->counter);
if (find(ptr,val->value))
    {
        //
        newNode=search(ptr,val->value);

        newNode->counter=newNode->counter+val->counter;
        cout<<"!!!"<<newNode->counter<<" "<<newNode->value<<"___"<<val->counter<<" "<<val->value<<endl;
    }
    else if(!find(root,val->value))
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
Treap::Node *Treap::search(Node *t, int value)
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


void Treap::remove(Node *ptr,int val)
{
    Node  *parent=0, *x;

    while(ptr)
    {
        if(val == ptr->value)
            break;
        else
        {
            parent = ptr;
            ptr = val < ptr->value ? ptr->left : ptr->right;
        }
    }

    if(ptr)
    {
        if (ptr->left == 0 || ptr->right == 0)
        {
            x = ptr->left!=0 ? ptr->left : ptr->right;
            if(ptr == root)
            {
                delete root;
                root = x;
            }
            else
            {
                if(parent->left == ptr)
                    parent->left = x;
                else parent->right = x;
                delete ptr;
                ptr = 0;
            }
        }
        else
        {
            x = ptr->right;
            while(x->left)
                x = x->left;
            int value = x->value;
            remove(x->value);
            ptr->value = value;
        }
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

