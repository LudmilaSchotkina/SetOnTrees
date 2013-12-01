#ifndef NVI_H
#define NVI_H

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
    void removeElement(int);
    void removeAllTree();
    void output();

    Iterator begin();
    Iterator end();

private:
    virtual void insert(int) = 0;
    virtual bool find(int) = 0;
    virtual void remove(int) = 0;
    virtual void removeAll() = 0;
    virtual void print() = 0;

    virtual void copy(const TreeInterface*) {}

    int &asterisc(void*);
    void next(void*&);
    void previous(void*&);

    virtual int &asteriscImpl(void*) = 0;
    virtual void nextImpl(void*&) = 0;
    virtual void previousImpl(void*&) = 0;

    virtual void *beginImpl() = 0;
};


class Iterator
{
public:
    friend class TreeInterface;

    Iterator();
    ~Iterator();
    Iterator (TreeInterface*, void*);

    int &operator*();
    Iterator operator++();
    Iterator operator++(int);

    bool operator==(const Iterator&);
    bool operator!=(const Iterator&);

private:
    TreeInterface *owner;
    void *cur;
};

#endif
