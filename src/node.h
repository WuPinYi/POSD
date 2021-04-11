#ifndef NODE_H
#define NODE_H

#include <string>
#include <vector>
#include <regex>
#include <sys/stat.h>
using namespace std;

class Node {
public:
  Node(string path): _path(path) {
    stat(_path.c_str(), &_st);
    if(stat(_path.c_str(), &_st)!=0) {
      throw string("Node is not exist!");
    }
  }
  string path()
  {
    return _path;
  }
  // For example path:"test/TA_folder/hello.txt"
  // "hello.txt" is name
  // Return "hello.txt"
  string name()
  {
    // _path = "test/test_folder/hello.txt";
    vector<string> _namePath;
    _namePath = split(_path, "/");
    return _namePath[_namePath.size()-1];
  }
  // implementation findNode
  // folder->findNode(name) that should find all nodes(include child nodes and all offspring) under it. 
  // file->findNode(name) that should find itself.
  // if find two nodes or more than two nodes.
  // Result should be separated by '\n'.
  virtual string findNode(string name)
  {
    return "";
      
  }
  virtual void addChild(Node* child) {
    throw string("Invalid add!");
  }

  virtual Node* getChild(int num) {
    return nullptr;
  }

  virtual string find(string name)
  {
    return "";
  }

  virtual string listNode()
  {
      return "";
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
