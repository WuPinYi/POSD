#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H
#include "node_iterator.h"

class NullIterator: public NodeIterator
{
    public:
        void first()
        {
        }

        Node* currentItem()
        {
            return nullptr;
        }

        void next()
        {
        }

        bool isDone()
        {
            return true;
        }
};
#endif