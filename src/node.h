#ifndef NODE_H
#define NODE_H

#include <sys/stat.h>
#include <vector>
#include <string>
#include <map>
#include "node_visitor.h"
#include "node_iterator.h"

class Node
{
    public:
        Node(const char* path):_path(path)
        {
            lstat(_path, &_st);
            std::vector<std::string> splitResult = split(_path, "/");
            _nodeName = splitResult[splitResult.size() - 1];
        }

        int size() const
        {
            return _st.st_size;
        }

        std::string name()
        {
            return _nodeName;
        }

        virtual void add(Node* node)
        {
            throw std::string("unable to add");
        }

        virtual int numberOfChildren()
        {
            throw std::string("number of children: not applicable");
        }

        virtual void accept(NodeVisitor* nodeVisitor) = 0;
        virtual void acceptChild(NodeVisitor* nodeVisitor) = 0;

        virtual NodeIterator* createIterator()
        {
            return nullptr;
        }

        Node* getParent() const
        {
            return _parent;
        }

        void setParent(Node* parent)
        {
            _parent = parent;
        }

        static std::vector<std::string> split(std::string s, std::string delimiter)
        {
            std::vector<std::string> result;
            for (int index = 0; index < s.size();)
            {
                result.push_back(s.substr(index, s.find(delimiter, index) - index));

                if (s.find(delimiter, index) == std::string::npos)
                {
                    break;
                }
                index = index + (s.find(delimiter, index) - index + delimiter.size());
            }
            return result;
        }
    private:
        const char* _path;
        struct stat _st;
        std::string _nodeName;
        Node* _parent;
};

#endif
