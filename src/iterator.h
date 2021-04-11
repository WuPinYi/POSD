#ifndef ITERATOR_H
#define ITERATOR_H
using namespace std;
class Node;

class Iterator
{
    public:
        virtual ~Iterator()
        {
        }
        virtual void first() = 0;
        virtual Node* currentItem() = 0;
        virtual void next() = 0;
        virtual bool isDone() = 0;
};


#endif
