#ifndef NODE_VISITOR_H
#define NODE_VISITOR_H

#include <string>

class File;
class Folder;
class Link;

class NodeVisitor
{
    public:
        virtual void visitFile(File* file) = 0;
        virtual void visitFolder(Folder* folder) = 0;
        virtual void visitLink(Link* link) = 0;
        virtual std::string findResult() = 0;
        virtual void clearResult() = 0;
};
#endif
