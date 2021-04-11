#ifndef FIND_LINK_VISITOR_CPP
#define FIND_LINK_VISITOR_CPP
#include "find_link_visitor.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "node_iterator.h"

FindLinkVisitor::FindLinkVisitor()
{
}

void FindLinkVisitor::visitFile(File* file)
{
}

void FindLinkVisitor::visitFolder(Folder* folder)
{
    NodeIterator* nodeIterator = folder->createIterator();
    for (nodeIterator->first(); !nodeIterator->isDone(); nodeIterator->next())
    {
        nodeIterator->currentItem()->acceptChild(this);
    }
}

void FindLinkVisitor::visitLink(Link* link)
{
    _links.push_back(link);
}

std::vector<Node*> FindLinkVisitor::getLinks()
{
    return _links;
}

void FindLinkVisitor::clearResult()
{
    _links.clear();
}

std::string FindLinkVisitor::findResult()
{
    return "";
}
#endif