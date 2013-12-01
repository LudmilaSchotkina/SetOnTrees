#ifndef SET_H
#define SET_H

#include "nvi.h"

class Set
{
public:

    Set(TreeInterface *object);

    ~Set();

    void insertValue (int);
    int findValue (int);
    void removeValue(int);
    void removeAll();

    void outputTree();
    void outputSet();

    Set &operator=(const Set&);
    Set operator+(Set&);
    Set operator-(Set&);
    Set operator^(Set&);

private:
    Set();
    TreeInterface *object;

};


#endif
