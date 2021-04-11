#ifndef FIND_NODE_BY_PATHNAME_VISITOR_CPP
#define FIND_NODE_BY_PATHNAME_VISITOR_CPP
#include "find_node_by_pathname_visitor.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "node_iterator.h"

FindNodeByPathnameVisitor::FindNodeByPathnameVisitor(std::vector<std::string>* pathnames):_pathnames(pathnames)
{
}

void FindNodeByPathnameVisitor::visitFile(File* file)
{
    if (isPathMatched(file))
    {
        _nodes.push_back(file);
    }
}

void FindNodeByPathnameVisitor::visitFolder(Folder* folder)
{
    // if (_isFirstNode)
    // {
    //     _isFirstNode = false;
    // }
    // else
    // {
        if (isPathMatched(folder))
        {
            _nodes.push_back(folder);
        }
    // }
    NodeIterator* nodeIterator = folder->createIterator();
    for (nodeIterator->first(); !nodeIterator->isDone(); nodeIterator->next())
    {
        nodeIterator->currentItem()->acceptChild(this);
    }
}

void FindNodeByPathnameVisitor::visitLink(Link* link)
{
    // if (_isFirstNode)
    // {
    //     _isFirstNode = false;
    // }
    if (isPathMatched(link))
    {
        _nodes.push_back(link);
    }
    if (link->getSource() != nullptr)
    {
        link->getSource()->acceptChild(this);
    }
}

bool FindNodeByPathnameVisitor::isPathMatched(Node* node)
{
    if (_pathnames->size() == 0)
    {
        return false;
    }
    Node* tempNode = node;
    for (std::vector<std::string>::reverse_iterator iter = _pathnames->rbegin(); iter != _pathnames->rend(); iter++)
    {
        if (tempNode == nullptr || tempNode->name() != *iter)
        {
            return false;
        }
        else
        {
            tempNode = tempNode->getParent();
        }
    }
    return true;
}

// return the Node object if the path indicate the node in the file system, and if not, return nullptr.
Node* FindNodeByPathnameVisitor::getNode() const
{
    if (_nodes.size() == 0)
    {
        return nullptr;
    }
    else
    {
        return _nodes[0];
    }
}

void FindNodeByPathnameVisitor::clearResult()
{
    _nodes.clear();
    _isFirstNode = true;
}

std::string FindNodeByPathnameVisitor::findResult()
{
    return "";
}
#endif