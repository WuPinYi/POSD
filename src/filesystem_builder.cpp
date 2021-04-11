#include "filesystem_builder.h"
#include "file.h"
#include "folder.h"
#include "link.h"
#include <sys/stat.h>
#include <string>
#include <dirent.h>

using namespace std;
FileSystemBuilder* FileSystemBuilder::_instance = nullptr;
FileSystemBuilder::FileSystemBuilder(){}
FileSystemBuilder* FileSystemBuilder::instance()
{
    if (_instance == nullptr)
    {
        _instance = new FileSystemBuilder;
    }
    return _instance;
}

void FileSystemBuilder::build(string path)
{
    struct stat st;
    // lstat(path.c_str(), &st);
    if (lstat(path.c_str(), &st) == 0)
    {
        if (S_ISREG(st.st_mode))
        {
            _root = new File(path);
        }
        else if (S_ISLNK(st.st_mode))
        {
            _root = new Link(path);
        }
        else if (S_ISDIR(st.st_mode))
        {
            _root = new Folder(path);
            DIR* dir = opendir(path.c_str());
            if (dir == nullptr)
            {
                throw std::string("open folder error");
            }
            struct dirent* entry = nullptr;
            while ((entry = readdir(dir)) != nullptr)
            {
                if (std::string(entry->d_name) != "." && std::string(entry->d_name) != "..")
                {
                    FileSystemBuilder fsb;
                    std::string temp = std::string(path) + "/" + entry->d_name;
                    const char* pathName = temp.c_str();
                    fsb.build(pathName);
                    _root->addChild(fsb.getRoot());
                }
            }
        }
    }
}
Node* FileSystemBuilder::getRoot()
{
    return _root;
}
