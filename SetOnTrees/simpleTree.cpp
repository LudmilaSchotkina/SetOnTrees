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
    removeAll();
}

void SimpleTree::removeAll()
{
    removeAll(root);
}

void SimpleTree::copy(const TreeInterface *orig)
{
    copyNode(root,((const SimpleTree *)orig)->root);
}

void SimpleTree::insert(int val)
{
    insert(root, val);
}
bool SimpleTree::find(int key)
{
    return find(root, key);
}
void SimpleTree::remove(int val)
{
    remove(root, val);
}
void SimpleTree::removeAll(Node *&ptr)
{
    if(ptr)
    {
        removeAll(ptr->left);
        removeAll(ptr->right);
        delete ptr;
    }
}
void SimpleTree::print()
{
    print(root,0);
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

void SimpleTree::insert(Node *&ptr, int val)
{
    if (ptr==0)
        ptr=new Node(val);
    else if (val < ptr->value)
        insert(ptr->left,val);

    else if (val > ptr->value)
        insert(ptr->right,val);

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


void SimpleTree::remove(Node *ptr,int val)
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
