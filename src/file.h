#ifndef FILE_H
#define FILE_H

#include "node.h"
#include "null_iterator.h"

class File: public Node
{
    public:
        File(const char* path):Node(path)
        {
            struct stat st;
            if (lstat(path, &st) == 0 && !S_ISREG(st.st_mode))
            {
                throw std::string("Do no indicate the file path.");
            }
        }
        
        void accept(NodeVisitor* nodeVisitor)
        {
            nodeVisitor->clearResult();
            nodeVisitor->visitFile(this);
        }

        void acceptChild(NodeVisitor* nodeVisitor)
        {
            nodeVisitor->visitFile(this);
        }

        NodeIterator* createIterator()
        {
            return new NullIterator();
        }
};
#endif