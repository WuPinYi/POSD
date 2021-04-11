#ifndef NODE_H
#define NODE_H

#include <vector>
#include <string>
#include <regex>
#include <sys/stat.h>
#include <stdio.h>
#include <iostream>
#include "visitor.h"
#include "iterator.h"

using namespace std;

class Node {
public:
  Node(string path): _path(path) {
    lstat(_path.c_str(), &_st);
    if(stat(_path.c_str(), &_st)!=0) {
      throw string("Node is not exist!");
    }
    vector<string> _namePath;
    _namePath = split(_path, "/");
    _name=_namePath[_namePath.size()-1];
  }

  virtual ~Node(){}

  int size() {
    return _st.st_size;
  }
  virtual void addChild(Node* child) {
    throw(string("Invalid add!"));
  }
  virtual int numberOfChildren()
  {
    throw string("number of children: not applicable");
  }
  virtual Iterator *createIterator() = 0;
  string getName()
  {
    return _name;
  }
  // Getter!
  // return node path
  string getPath()
  {
    return _path;
  }
  void setPath(string new_path)
  {
    _path = new_path;
  }
  void renamePath(vector<string> new_path) {
    vector<string> old_path = split(_path, "/");
    string path = "";
    for(int i = 0; i < old_path.size(); i++) 
    {
      if(new_path.size() > i){
        path += new_path[i];
      }
      else{
        path += old_path[i];
      }
      if(i < old_path.size() - 1)
      {
        path += "/";
      }   
    }
    _path = path;
  }
  /* You should update 
    1. The physical node name.
    2. The node name in your own file system
  */
  void renameNode(string new_name) {
    vector<string> new_path = split(new_name, "/");
    if(new_path.size() == 1) 
    {
      string file_path = _path;
      size_t start_pos = _path.find(_name);
      _path = _path.replace(start_pos, _name.length(), new_name);
      rename(file_path.c_str(), _path.c_str());
      _name = new_name;
    } else 
      renamePath(new_path);
}
  virtual void accept(Visitor* visitor) = 0;
  virtual void acceptChild(Visitor* visitor) = 0;
  static vector<string> split(const string& str, const string& delim) 
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
private:
  string _path;
  string _name;
  string _old_name;
  string _new_name;
  struct stat _st;
  // split
  

};


#endif
