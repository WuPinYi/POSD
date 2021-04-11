#ifndef FILESYSTEM_BUILDER_H
#define FILESYSTEM_BUILDER_H
#include "visitor.h"
#include "node.h"
#include <string>
#include <vector>
using namespace std;

class FileSystemBuilder  {
    protected:
        FileSystemBuilder();
    public:
        static FileSystemBuilder * instance();
        void build(string path);
        Node * getRoot();
    private:
        static FileSystemBuilder* _instance;
        Node * _root;
};



#endif
