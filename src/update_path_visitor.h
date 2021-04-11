#ifndef UPDATE_PATH_VISITOR_H
#define UPDATE_PATH_VISITOR_H
#include "visitor.h"
#include <string>
#include "node.h"
using namespace std;
class UpdatePathVisitor: public Visitor
{
    public:
        UpdatePathVisitor();
        void visitFolder(Folder * folder);
        void visitFile(File * file);
        void visitLink(Link * link);
        void clearVisitor();
        string findResult();
        void clearResult();
    private:
        string _oldName = "";
        string _newName = "";
        string _newPath = "";
};
#endif