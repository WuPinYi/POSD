#ifndef LINK_H
#define LINK_H

#include "node.h"
#include <sys/stat.h>
#include <string>
using namespace std;

class Link: public Node{
public:
  // You should check path if it is not a link that you should throw string "It is not Link!"
  Link(string path, Node* node):Node(path){
    lstat(path.c_str(), &_st);
    if(!S_ISLNK(_st.st_mode))
    {
      throw string("It is not Link!");
    }
    this->addLink(node);
  }

  void accept(Visitor* visitor) // accept visitor
  {
    visitor->clearResult();
    visitor->visitLink(this);
  }
  void acceptChild(Visitor* visitor)
  {
    visitor->visitLink(this);
  }
  void addLink(Node * node) // add symbolic link
  {
    _source = node;
  }
  Node * getSource() // return node that the link point to!
  {
    return _source;
  }
  Iterator* createIterator() // return null Iterator
  {
    return new NullIterator();
  }
private:
  Node* _source;
  struct stat _st;
};
#endif