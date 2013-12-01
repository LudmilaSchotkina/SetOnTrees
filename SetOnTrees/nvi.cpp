#include "nvi.h"
#include "treap.h"

TreeInterface::TreeInterface(const TreeInterface &orig)
{
    copy(&orig);
}

TreeInterface::~TreeInterface()
{
    removeAllTree();
}

void TreeInterface::insertElement(int val)
{
    insert(val);
}

bool TreeInterface::findElement(int val)
{
    return find(val);
}

void TreeInterface::removeElement(int val)
{
    remove(val);
}

void TreeInterface::removeAllTree()
{
    removeAll();
}

void TreeInterface::output()
{
    print();
}

//////////////////////////////////////////////////////

Iterator::Iterator():
    owner(0),
    cur(0)
{}

Iterator::Iterator(TreeInterface *owner, void *cur):
    owner(owner),
    cur(cur)
{}

Iterator::~Iterator()
{
    owner = 0;
    cur = 0;
}

int &Iterator::operator*()
{
    if(owner)
        return owner->asterisc(cur);
    else throw -1;
}

Iterator Iterator::operator++()
{
    if(owner)
        owner->next(cur);
    return *this;
}

Iterator Iterator::operator++(int)
{
    Iterator result(*this);
    ++(*this);
    return result;
}

bool Iterator::operator==(const Iterator &smth)
{
    return owner == smth.owner && cur == smth.cur;
}

bool Iterator::operator!=(const Iterator &smth)
{
    return !(*this == smth);
}

/////////////////////////////////////////////
int &TreeInterface::asterisc(void *ptr)
{
    return asteriscImpl(ptr);
}

Iterator TreeInterface::begin()
{
    return Iterator(this, beginImpl());
}

Iterator TreeInterface::end()
{
    return Iterator(this, 0);
}

void TreeInterface::next(void *&ptr)
{
    nextImpl(ptr);
}

void TreeInterface::previous(void *&ptr)
{
    previousImpl(ptr);
}
