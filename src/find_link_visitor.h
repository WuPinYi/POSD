#ifndef FIND_LINK_VISITOR_H
#define FIND_LINK_VISITOR_H
#include "node.h"
#include "node_visitor.h"
#include <vector>

class FindLinkVisitor: public NodeVisitor
{
    public:
        FindLinkVisitor();
        void visitFile(File* file);
        void visitFolder(Folder* folder);
        void visitLink(Link* link);
        std::vector<Node*> getLinks();
        void clearResult();
        std::string findResult();
    private:
        std::vector<Node*> _links;
};
#endif