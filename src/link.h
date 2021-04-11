#ifndef LINK_H
#define LINK_H
#include "node.h"

class Link: public Node
{
    public:
        Link(const char* path, Node* node = nullptr):Node(path)
        {
            struct stat st;
            if (lstat(path, &st) == 0 && !S_ISLNK(st.st_mode))
            {
                throw std::string("Do no indicate the link path.");
            }
            this->addLink(node);
        }

        void addLink(Node* node)
        {
            _source = node;
        }

        Node* getSource()
        {
            return _source;
        }

        void accept(NodeVisitor* nodeVisitor)
        {
            nodeVisitor->clearResult();
            nodeVisitor->visitLink(this);
        }

        void acceptChild(NodeVisitor* nodeVisitor)
        {
            nodeVisitor->visitLink(this);
        }

        NodeIterator* createIterator()
        {
            return new NullIterator();
        }
    private:
        Node* _source;
};

#endif
