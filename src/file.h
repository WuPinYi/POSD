#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include <regex>
#include <sys/stat.h>
#include "node.h"

using namespace std;

class File: public Node {
public:
  File(string path): Node(path) {
    stat(path.c_str(), &_st);
    if (!S_ISREG (_st.st_mode) )
    {
      throw string("It is not File!");
    }
    _name = name();
  }
  string findNode(string name)
  {
    if (_name == name)
      return name;
    return "";
  }
  string listNode()
  {
    throw string("Not a directory");
  }

private:
  struct stat _st;
  string _name;
  
};

#endif
