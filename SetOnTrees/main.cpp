#include <iostream>
#include <fstream>
#include "set.h"
#include "nvi.h"
#include "treap.h"
#include "simpleTree.h"

using namespace std;

int main()
{
    Treap *treap = new Treap;
    Treap *treap2 = new Treap;
    Set setTree(treap);
    Set setTree2(treap2);


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
        setTree.insertValue(value);
    }
    fileTreap.close();
    setTree.outputTree();
    cout<<endl<<endl<<endl;
    cout<<"Bypass (Set): ";
    setTree.outputSet();
    cout<<endl<<endl;

    cout<<"_____________TREE 2__________________"<<endl<<endl;

    fstream fileTreap2;
    fileTreap2.open("treap2.txt");

    if(!fileTreap2)
    {
        cerr<<"Error 404"<<endl;
        return -1;
    }

    while(!fileTreap2.eof())
    {
        fileTreap2>>value;
        setTree2.insertValue(value);
    }
    fileTreap2.close();
    setTree2.outputTree();
    cout<<endl<<endl;
    cout<<"Bypass (Set): ";
    setTree2.outputSet();
    cout<<endl<<endl<<endl;


    int choise;

    cout<<"1 - unite "<<endl<<"2 - difference "<<endl<<"3 - intersect "<<endl<<"0 - exit "<<endl;
    cin>>choise;
    switch (choise)
    {
    case 0:
        choise=0;
        break;
    case 1:
        cout<<"++++++++++++++++++UNION++++++++++++++++++"<<endl<<endl;
        (setTree+setTree2).outputTree();
        break;
    case 2:
        cout<<"---------------DIFFERENCE---------------"<<endl<<endl;
        (setTree2-setTree).outputSet();
        cout<<endl<<endl<<endl;
        break;
    case 3:
        cout<<"^^^^^^^^^^^^^^^INTERSECTION^^^^^^^^^^^^^^^^"<<endl<<endl;
        (setTree2^setTree).outputSet();
        cout<<endl<<endl<<endl;
        break;
    default:
        cout<<"wrong key"<<endl;
        break;
    }
    return 0;
}
