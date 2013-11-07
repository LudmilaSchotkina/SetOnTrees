#include <iostream>
#include <fstream>
#include "set.h"
#include "nvi.h"
#include "treap.h"
#include "simpleTree.h"

using namespace std;

int main()
{
    Treap tree;
    //SimpleTree tree;

    int value;
    fstream fileTreap;
    fileTreap.open("treap.txt");

    if(!fileTreap)
    {
        cerr<<"Error 404"<<endl;
        return -1;
    }

    cout<<"_____________TREE 1__________________"<<endl<<endl;
    while(!fileTreap.eof())
    {
        fileTreap>>value;
        tree.insert(value);
    }
    fileTreap.close();
    tree.print();
    cout<<endl<<endl<<endl;


    cout<<"_____________TREE 2__________________"<<endl<<endl;

    Treap tree2;
    //SimpleTree tree2;

    fstream file;
    file.open("treap2.txt");

    if(!file)
    {
        cerr<<"Error 404"<<endl;
        return -1;
    }

    while(!file.eof())
    {
        file>>value;
        tree2.insert(value);
    }
    file.close();
    tree2.print();
    cout<<endl<<endl<<endl;


    Treap c,d,e;
    //SimpleTree c,d,e;

    cout<<"---------------DIFFERENCE---------------"<<endl<<endl;
    d=tree-tree2;
    d.print();
    cout<<endl<<endl<<endl;

    cout<<"^^^^^^^^^^^^^^^INTERSECT^^^^^^^^^^^^^^^^"<<endl<<endl;
    e=tree2^tree;
    e.print();
    cout<<endl<<endl<<endl;

    cout<<"++++++++++++++++++UNION++++++++++++++++++"<<endl<<endl;
    c=tree+tree2;

    c.print();

    return 0;
}
