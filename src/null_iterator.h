#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H

#include <string>
#include "iterator.h"

using namespace std;

class NullIterator:public Iterator
{
  public:
    //throw string "no child member"
    void first(){
        throw string("no child member");
    }
    //throw string "no child member"
    Node* currentItem(){
        throw string("no child member");
    }
    //throw string "no child member"
    void next() {
        throw string("no child member");
    }
    bool isDone(){
      return true;
    }
};
#endif