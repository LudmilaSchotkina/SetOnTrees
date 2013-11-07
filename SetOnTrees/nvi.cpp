#include "nvi.h"
#include "treap.h"

void TreeInterface::insertTreap(Node *&ptr, Node *val)
{
    insert(val->value);
}

void TreeInterface::insertTree(Node *&ptr, int val)
{
    insert(val);
}

