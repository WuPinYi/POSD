#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H

#include <string>
#include "node.h"
#include "iterator.h"
using namespace std;

class NullIterator:public Iterator
{
  public:
    NullIterator(){}
    //throw string "no child member"
    void first(){
        throw string("No child member!");
    }
    //throw string "no child member"
    Node* currentItem(){
        throw string("No child member!");
    }
    //throw string "no child member"
    void next() {
        throw string("No child member!");
    }
    bool isDone(){
      return true;
    }
};
#endif
