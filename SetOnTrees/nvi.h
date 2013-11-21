#ifndef NVI_H
#define NVI_H

struct Node;
class Iterator;

class TreeInterface //NVI
{
public:
    friend class Iterator;

    TreeInterface() {}
    TreeInterface(const TreeInterface &orig);
    ~TreeInterface();

    void insertElement(int);
    bool findElement(int);
    void removeAll();

    Iterator begin();
    Iterator end();

private:
    virtual void insert(int) = 0;
    virtual bool find(int) = 0;
    virtual void deleteAll() {};

    virtual void copy(const TreeInterface*) {}

    int &asterisc(void*);
    void next(void*&);
    void previous(void*&);

    virtual int &asteriscImpl(void*) = 0;
    virtual void nextImpl(void*&) = 0;
    virtual void previousImpl(void*&) = 0;

    virtual void *beginImpl() = 0;
    // virtual void *endImpl() = 0;

};

class Iterator
{
public:
    friend class TreeInterface;

    Iterator();
    ~Iterator();

    int &operator*();
    Iterator operator++();
    Iterator operator++(int);

    Iterator operator--();
    Iterator operator--(int);

    bool operator==(const Iterator&);
    bool operator!=(const Iterator&);

    Iterator (TreeInterface*, void*);

private:
    TreeInterface *owner;
    void *cur;

};

#endif
