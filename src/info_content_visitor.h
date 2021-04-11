#ifndef NODE_VISITOR_H
#define NODE_VISITOR_H
#include "node_visitor.h"

class InfoContentVisitor: public NodeVisitor
{
    public:
        InfoContentVisitor();
        void visitFile(File* file);
        void visitFolder(Folder* folder);
        void visitLink(Link* link);
        int getContentSize();
        void clearResult();
        std::string findResult();
    private:
        int _size;
};
#endif