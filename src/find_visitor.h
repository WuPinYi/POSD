#ifndef FIND_VISITOR_H
#define FIND_VISITOR_H

#include "node_visitor.h"
#include <vector>

class FindVisitor: public NodeVisitor
{
    public:
        FindVisitor(std::string target);
        void visitFile(File* file);
        void visitFolder(Folder* folder);
        void visitLink(Link* link);
        std::string findResult();
        void clearResult();
    private:
        void assembleResult(std::vector<std::string> tempResult);
        std::string _target;
        std::string _traversal;
        std::string _result;
};
#endif