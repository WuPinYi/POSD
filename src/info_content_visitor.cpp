#ifndef INFO_CONTENT_VISITOR_H
#define INFO_CONTENT_VISITOR_H
#include "info_content_visitor.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "node_iterator.h"

InfoContentVisitor::InfoContentVisitor()
{
}

void InfoContentVisitor::visitFile(File* file)
{
    _size += file->size();
}

void InfoContentVisitor::visitFolder(Folder* folder)
{
    NodeIterator* nodeIterator = folder->createIterator();
    for (nodeIterator->first(); !nodeIterator->isDone(); nodeIterator->next())
    {
        nodeIterator->currentItem()->acceptChild(this);
    }
}

void InfoContentVisitor::visitLink(Link* link)
{
}

int InfoContentVisitor::getContentSize()
{
    return _size;
}

void InfoContentVisitor::clearResult()
{
    _size = 0;
}

std::string InfoContentVisitor::findResult()
{
    return "";
}
#endif