#ifndef FILE_H
#define FILE_H

#include <string>
#include <sys/stat.h>

#include "node.h"
#include "null_iterator.h"
using namespace std;
class File: public Node {
public:
  File(std::string path): Node(path) {
    lstat(path.c_str(), &_st);
    if (!S_ISREG (_st.st_mode) )
    {
      throw string("It is not File!");
    }

  }
  Iterator * createIterator() 
  {
    return new NullIterator();
  }
  void accept(Visitor* visitor)
  {
    visitor->clearResult();
    visitor->visitFile(this);
  }
  void acceptChild(Visitor* visitor)
  {
    visitor->visitFile(this);
  }
private:
  struct stat _st;
};

#endif
