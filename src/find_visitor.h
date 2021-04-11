#ifndef FIND_VISITOR_H
#define FIND_VISITOR_H
#include "visitor.h"
#include <string>

using namespace std;

class FindVisitor: public Visitor
{
    public:
        FindVisitor(string name); // Name is the target we want to find.
        void visitFolder(Folder * folder);
        void visitFile(File * file);
        void visitLink(Link * link); // You only need to check the link itself,and you don't have to check the node that the link point to!  
        string findResult();
        void clearResult();
    private:
        string _path;
        string _name;
        string _result;
        string _traversal;
};
#endif