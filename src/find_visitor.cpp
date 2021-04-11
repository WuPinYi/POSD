#include "find_visitor.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include <vector>
#include <iostream>
#include <regex>
// #include "node_iterator.h"

using namespace std;

FindVisitor::FindVisitor(string name):_name(name)
{
}
void FindVisitor::visitFolder(Folder* folder)
{
    Iterator* it = folder->createIterator();

    if (_traversal == "")
    {
        _traversal += ".";
    }
    else
    {
        _traversal += "/" + folder->getName();
    }

    if (folder->numberOfChildren() == 0)
    {
        _traversal += "/<file>";
        return;
    }
    if (folder->numberOfChildren() > 1)
    {
        _traversal += "/<folder>" + std::to_string(folder->numberOfChildren());
    }

    for (it->first(); !it->isDone(); it->next())
    {
        it->currentItem()->acceptChild(this);
    }
}
void FindVisitor::visitFile(File* file)
{
    if (_traversal == "")
    {
        _traversal += file->getName();
    }
    else
    {
        _traversal += "/" + file->getName() + "/<file>";
    }
}
void FindVisitor::visitLink(Link* link)
{
    if (_traversal == "")
    {
        _traversal += link->getName();
    }
    else
    {
        _traversal += "/" + link->getName() + "/<file>";
    }
}

string FindVisitor::findResult()
{   
    vector<string> splitResult = Node::split(_traversal, "/");
    for (int i = 0; i < splitResult.size(); i++)
    {
        if (splitResult[i] == _name)
        {
            int counter = 0;
            vector<string> tempResult;
            for (int j = i; j > -1; j--)
            {
                if (splitResult[j] == "<file>")
                {
                    counter += 1;
                    continue;
                }
                if (splitResult[j].substr(0, 8) == "<folder>")
                {
                    counter -= std::stoi(splitResult[j].substr(8, 1));
                    continue;
                }
                if (counter <= 0)
                {
                    tempResult.push_back(splitResult[j]);
                }
            }
            string singleResult;
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
    }
    return _result;
}

void FindVisitor::clearResult()
{
    _traversal = "";
    _result = "";
}
