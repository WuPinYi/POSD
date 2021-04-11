#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <sys/stat.h>
#include <vector>
#include <map>
#include "node.h"
#include "iterator.h"

using namespace std;

class Folder: public Node {
public:
  class FolderIterator:public Iterator {
  public:
    FolderIterator(Folder * f): _f(f) {}
    // initialization
    void first() {
      _current = _f->_map.begin();
    }
    // if iterator is to the end that it should throw string "No current item!"
    // if iterator is not to the end that it should return current node
    Node * currentItem() {
      if (isDone()) throw string("No current item!");
      return (*_current).second;
    }
    // if iterator is to the end that it should throw string "Moving past the end!"
    // if iterator is not to the end that it should add 1
    void next() {
      if (isDone()) throw string("Moving past the end!");
      ++_current;
    }
    // return iterator is to the end or not?
    bool isDone() {
      return _current == _f->_map.end();
    }
  private:
    Folder * _f;
    map<string,Node *>::iterator _current;
  };

public:
  Folder(std::string path): Node(path) {
  }

  void addChild(Node* child) {
    string fileName = child->getName();
    _map.insert(pair<string,Node *>(fileName,child));
  }

  Iterator * createIterator() {
    return new FolderIterator(this);
  }
  map<string,Node *> getMap() {
    return _map;
  }

private:
  map<string,Node *> _map;
};
#endif
