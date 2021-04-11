#ifndef VISTOR_H
#define VISTOR_H
#include <string>

using namespace std;

class File;
class Folder;
class Link;

class Visitor
{
  public:
    virtual ~Visitor(){}
    virtual void visitFolder(Folder * folder) = 0;
    virtual void visitFile(File * file) = 0;
    virtual void visitLink(Link * link) = 0;
    virtual string findResult() = 0;
    virtual void clearResult() = 0;
};
#endif
