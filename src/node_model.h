#ifndef NODE_MODEL_H
#define NODE_MODEL_H

#include "subject.h"
#include "node.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "node_builder.h"

class NodeModel: public Subject
{
    public:
        NodeModel(std::string rootPath):_rootPath(rootPath)
        {
            this->buildRootNode();
        }

        void refresh()
        {
            this->buildRootNode();
            this->notify();
        }

        Node* getRootNode()
        {
            return _rootNode;
        }
    private:
        void buildRootNode()
        {
            NodeBuilder nodeBuilder;
            nodeBuilder.build(_rootPath.c_str());
            _rootNode = nodeBuilder.getRoot();
        }

        std::string _rootPath;
        Node* _rootNode;
};

#endif
