#include <iostream>
#include "set.h"

Set::Set():
    object(0)
{}

Set::Set(TreeInterface *object):
    object(object)
{}

Set::~Set()
{
    removeAll();
}

void Set::insertValue(int value)
{
    object->insertElement(value);
}

int Set::findValue(int value)
{
    return object->findElement(value);
}

void Set::removeValue(int value)
{
    object->removeElement(value);
}

void Set::outputTree()
{
    object->output();
}

void Set::outputSet()
{
    for(Iterator it=object->begin(); it!=object->end(); it++)
        std::cout << *it << " ";
}
void Set::removeAll()
{
    object->removeAllTree();
}
/////////////////////////////////////

Set &Set::operator=(const Set &orig)
{
    *(this->object) = *(orig.object);
    return *this;
}

Set Set::operator+(Set &orig)
{
    for(Iterator it=orig.object->begin(); it!=orig.object->end(); it++)
        this->insertValue(*it);

    return *this;
}

Set Set::operator-(Set &orig)
{
    for(Iterator it=orig.object->begin(); it!=orig.object->end(); it++)
        this->removeValue(*it);

    return *this;
}

Set Set::operator^(Set &orig)
{
    int *ar = new int [100], counter=0;  //don't ask me

    for(Iterator it=orig.object->begin(); it!=orig.object->end(); it++)
    {
        if(this->findValue(*it))
        {
            ar[counter]=*it;
            ++counter;
        }
    }
    this->removeAll();

    for(int i=0; i<counter; ++i)
        this->insertValue(ar[i]);

    delete []ar;
    return *this;
}
