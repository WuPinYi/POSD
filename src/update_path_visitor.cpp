#include "update_path_visitor.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include "iterator.h"
#include <iostream>
using namespace std;

UpdatePathVisitor::UpdatePathVisitor(){}
void UpdatePathVisitor::visitFolder(Folder* folder) {
    Iterator* it = folder->createIterator();
    if(_newPath == ""){
        _newPath = folder->getPath();
    }
    else{
        folder->renameNode(_newPath);
    }
    
    for (it->first(); !it->isDone(); it->next()) {
        it->currentItem()->accept(this);
    }
    // init
    if(folder->getPath() == _newPath)
    {
        clearVisitor();
    }
}

void UpdatePathVisitor::visitFile(File* file) 
{
    file->renameNode(_newPath);
}

void UpdatePathVisitor::visitLink(Link* link) 
{
    link->renameNode(_newPath);
}

void UpdatePathVisitor::clearVisitor() 
{
    _newPath = "";
}

string UpdatePathVisitor::findResult()
{
    return "";
}
void UpdatePathVisitor::clearResult() 
{
}