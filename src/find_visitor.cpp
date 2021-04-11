#ifndef FIND_VISITOR_CPP
#define FIND_VISITOR_CPP
#include "find_visitor.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "node_iterator.h"

FindVisitor::FindVisitor(std::string target):_target(target)
{
}

void FindVisitor::visitFile(File* file)
{
    if (_traversal == "")
    {
        _traversal += file->name();
    }
    else
    {
        _traversal += "/" + file->name() + "/<leaf>";
    }
}

void FindVisitor::visitFolder(Folder* folder)
{
    NodeIterator* nodeIterator = folder->createIterator();

    if (_traversal == "")
    {
        _traversal += ".";
    }
    else
    {
        _traversal += "/" + folder->name();
    }

    if (folder->numberOfChildren() == 0)
    {
        _traversal += "/<leaf>";
        return;
    }
    if (folder->numberOfChildren() > 1)
    {
        _traversal += "/<branch>" + std::to_string(folder->numberOfChildren());
    }

    for (nodeIterator->first(); !nodeIterator->isDone(); nodeIterator->next())
    {
        nodeIterator->currentItem()->acceptChild(this);
    }
}

void FindVisitor::visitLink(Link* link)
{
}

std::string FindVisitor::findResult()
{
    std::vector<std::string> splitResult = Node::split(_traversal, "/");
    for (int i = 0; i < splitResult.size(); i++)
    {
        if (splitResult[i] == _target)
        {
            int counter = 0;
            std::vector<std::string> tempResult;
            for (int j = i; j > -1; j--)
            {
                if (splitResult[j] == "<leaf>")
                {
                    counter += 1;
                    continue;
                }
                if (splitResult[j].substr(0, 8) == "<branch>")
                {
                    counter -= std::stoi(splitResult[j].substr(8, 1));
                    continue;
                }
                if (counter <= 0)
                {
                    tempResult.push_back(splitResult[j]);
                }
            }
            assembleResult(tempResult);
        }
    }
    return _result;
}

void FindVisitor::assembleResult(std::vector<std::string> tempResult)
{
    std::string singleResult;
    for (int index = tempResult.size() - 1; index > -1; index--)
    {
        singleResult += tempResult[index] + "/";
    }
    singleResult.erase(singleResult.size() - 1);

    if (_result == "")
    {
        _result += singleResult;
    }
    else
    {
        _result += "\n" + singleResult;
    }
}

void FindVisitor::clearResult()
{
    _traversal = "";
    _result = "";
}
#endif