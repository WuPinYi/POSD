#ifndef UTILITIES_H
#define UTILITIES_H

#include "folder.h"
#include <regex>
#include <sys/stat.h>
#include <string>
#include <map>
using namespace std;

class Utilities 
{
  public:
    // You should use iterator pattern to access node in folder!
    // You can use dynamic_cast if you need
    // If node is file that it should throw string "Not a directory"
    // This function is same as Hw4 listNode()
    string listNode(Node* node)
    {
        Folder * folder = dynamic_cast<Folder *> (node); // down cast
        //it's a folder
        if (folder != nullptr) { 
          Iterator * it = folder->createIterator();
          string list = "";
          map<string,Node *> map;
          map = folder->getMap();
          // sorting map by desending value
          // std::sort(map.begin(),map.end(),[](std::pair<string,Node *> a, std::pair<string,Node *> b){
          //   return a.first < b.first;
          // });
          for(it->first(); !it->isDone(); it->next())
          {
            Node * n = it->currentItem();
            list = list + n->getName();
            if (!it->isDone()) list = list + " ";
          }
          list = list.substr(0, list.length() - 1);
          return list;
        }
        else{
          throw string("Not a directory");
        }
    }
    // You should use iterator pattern to access node in folder!
    // You can use dynamic_cast if you need
    // This function is same as Hw4 findNode()
    string findNode(Node* node, string name)
    {
      Folder * folder = dynamic_cast<Folder *> (node);
      //it's a folder
      if (folder != nullptr) 
      {
        string nodeList = find(node,name);
        string validForm = getvalidRegexForm(node->path());
        regex Form(validForm);
        string st = regex_replace(nodeList, Form, ".") ;
        nodeList = st.substr(0, st.size()-1);

        return nodeList;
      }
      else{
        return name;
      } 
    }
    // find node name 
    string find(Node* node,string name)
    {
      Folder * folder = dynamic_cast<Folder *> (node); // down cast
      string result = "";
      Iterator * it = folder->createIterator();
      for(it->first(); !it->isDone(); it->next())
      {
        Folder * f = dynamic_cast<Folder *> (it->currentItem());
        if (f != nullptr) result+= find(it->currentItem(),name);
        if (it->currentItem()->getName()==name) result+=it->currentItem()->path()+"\n";
      }
      return result;
    }
  private:
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
