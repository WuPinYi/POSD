#ifndef NODE_H
#define NODE_H

#include <string>
#include <sys/stat.h>
#include "iterator.h"
#include <vector>

using namespace std;

class Node {
public:
  Node(string path): _path(path) {
    stat(_path.c_str(), &_st);
  }

  virtual ~Node(){}

  int size() {
    return _st.st_size;
  }

  virtual void addChild(Node* child) {
    throw(string("Invalid add!"));
  }
  virtual Iterator *createIterator() = 0;
  string getName()
  {
    vector<string> _namePath;
    _namePath = split(_path, "/");
    return _namePath[_namePath.size()-1];
  }
  string path()
  {
    return _path;
  }


private:
  string _path;
  struct stat _st;
  // split
  vector<string> split(const string& str, const string& delim) 
  {
    vector<string> res;
    // string to char
    char *strs = new char[str.length() + 1];
    // strcpy(copied, input)
    strcpy(strs, str.c_str()); 
    char *d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());
    char *p = strtok(strs, d);
    while(p) 
    {
        string s = p;
        res.push_back(s);
        p = strtok(NULL, d);
    }
    return res;
  }

};


#endif
