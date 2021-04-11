#ifndef FOLDER_H
#define FOLDER_H

#include <string>
#include <vector>
#include <regex>
#include <sys/stat.h>
#include "node.h"
using namespace std;

class Folder: public Node {
public:
  Folder(string path): Node(path) 
  {
    stat(path.c_str(), &_st);
    if (!S_ISDIR(_st.st_mode)) 
    {
      throw string("It is not Folder!");
    }
    _name = name();
    _path = path;
  }
  Node* getChild(int num) {
    if (_list.empty()) return nullptr;
    else return _list[num];
  }

  void addChild(Node* child) {
    _list.push_back(child);
  }
  string findNode(string name)
  {
    string nodeList = find(name);
    string validForm = getvalidRegexForm(_path);
    regex Form(validForm);
    string st = regex_replace(nodeList, Form, ".") ;
    nodeList = st.substr(0, st.size()-1);
   
    return nodeList;
  }
  // find node name 
  string find(string name)
  {
    string result = "";
    for (int i=0;i<_list.size();i++)
    {
      if (_list[i]->getChild(0) != nullptr) result += _list[i]->find(name);
      if (_list[i]->name() == name)
        result += _list[i]->path()+ "\n" ;
    }
    return result;
  }

  string listNode()
  {
    string list = "";
    std::sort(_list.begin(),_list.end(),[](Node* a, Node* b){
        return a->name() < b->name();
    });
    for (int i=0;i<_list.size();i++)
    {
      list = list + _list[i]->name();
      if (i!=_list.size()-1) list = list + " ";
    }
    return list;
  }

  
private:
  struct stat _st;
  string _name;
  string _path;
  vector<Node*> _list;
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

  string getvalidRegexForm(string path)
  {
    vector<string> validForm;
    validForm = split(path, "/");
    string result = "";
    for (int i=0 ; i< validForm.size();i++)
    {
      result = result + validForm[i];
      if (i!= validForm.size()-1) result = result + "+[/]+";
    }
    return result;
  }

};
#endif