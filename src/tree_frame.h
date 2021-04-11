#ifndef TREE_FRAME_H
#define TREE_FRAME_H

#include <wx/treectrl.h>
#include <wx/button.h>
#include <string>
#include <vector>
#include <fstream>
#include <sys/stat.h>

#include "observer.h"
#include "node_model.h"
#include "node_iterator.h"

enum {
    wxID_BUTTON = wxID_HIGHEST + 1
};

using namespace std;
class TreeFrame: public wxFrame, public Observer {
public:
    // 初始化視窗
    TreeFrame(const wxChar* title, string rootPath): wxFrame((wxFrame*)nullptr, -1, title, wxPoint(100, 100), wxSize(600, 400)), _rootPath(rootPath) {
        _treeCtrl = new wxTreeCtrl(this, wxID_ANY, wxPoint(0, 0), wxSize(200, 400), wxTR_DEFAULT_STYLE | wxTR_SINGLE | wxTR_EDIT_LABELS);

        _nodeModel = new NodeModel(rootPath);
        _nodeModel->attach(this);
        this->initialize();

        _textCtrl = new wxTextCtrl(this, -1, wxString("Welcome to POSD_EDITOR"), wxPoint(200, 0), wxSize(400, 350), wxTE_MULTILINE);
        _textCtrl->Enable(false);
        _button = new wxButton(this, wxID_BUTTON, wxString("Save"), wxPoint(200, 350), wxSize(400, 50));
        _button->Enable(false);
    }

    // click檔案
    void onClick(wxTreeEvent& event) {
        wxTreeItemId nodeId = event.GetItem();
        _currentPath = appendPath(nodeId);

        struct stat st;
        if (lstat(_currentPath.c_str(), &st) == 0) {
            if (S_ISREG(st.st_mode)) {
                vector<string> fileType = Node::split(_currentPath, ".");
                if(fileType.size() == 1) {
                    _textCtrl->SetValue(wxString("This file is not displayes in the editor because it uses an unsupported text encoding"));
                    _textCtrl->Enable(false);
                    _button->Enable(false);
                } else {
                    // 二進位檔
                    if (fileType[1] == "out") {
                        _textCtrl->SetValue(wxString("This file is not displayes in the editor because it uses an unsupported text encoding"));
                        _textCtrl->Enable(false);
                        _button->Enable(false);
                    } else {
                        _textCtrl->LoadFile(wxString(_currentPath));
                        _textCtrl->Enable(true);
                        _button->Enable(true);
                    }
                }
            }
            else if (S_ISLNK(st.st_mode)) {
                _textCtrl->SetValue(wxString("This is a link"));
                _textCtrl->Enable(false);
                _button->Enable(false);
            }
            else if (S_ISDIR(st.st_mode)) {
                _textCtrl->SetValue(wxString("This is a directory"));
                _textCtrl->Enable(false);
                _button->Enable(false);
            }
        }
    }

    void onEdit(wxTreeEvent& event) {
        wxTreeItemId oldNodeId = event.GetItem();
        string oldNodeName = _treeCtrl->GetItemText(oldNodeId).ToStdString();
        string newNodeName = event.GetLabel().ToStdString();
        // 如果沒有變動則直接return
        if (newNodeName == "" || Node::split(oldNodeName, ",")[0] == Node::split(newNodeName, ",")[0]) {
            event.Veto();
            return;
        }
        string message = "label edited: " + newNodeName + " -- old name was " + oldNodeName;
        wxMessageDialog* messageDialog = new wxMessageDialog(this, wxString(message), wxString("Confirm"), wxYES_NO | wxCANCEL);
        if (messageDialog->ShowModal() == wxID_YES) {
            if (renameFile(oldNodeId, newNodeName) == 0) {
                cout << "Node " << oldNodeName << " edited to " << newNodeName << endl;
            } else {
                cout << "Error node " << oldNodeName << " edited to " << newNodeName << endl;
            }
        } else {
            event.Veto();
            cout << "Edit file name canceled" << endl;
        }
    }

    // 儲存檔案
    void onSave(wxCommandEvent& event) {
        wxMessageDialog* messageDialog = new wxMessageDialog(this, wxString("Do you want to save?"), wxString("Confirm"), wxYES_NO | wxCANCEL);
        if (messageDialog->ShowModal() == wxID_YES)  {
            _textCtrl->SaveFile(wxString(_currentPath));
            _nodeModel->refresh();
            cout << "File " << _currentPath << " has been saved" << endl;
        }
    }

    // observer
    void update() {
        // 移除右方物件並更新
        _treeCtrl->DeleteAllItems();
        this->initialize();
        cout << "Frame updated" << endl;
    }

private:
    wxTreeCtrl* _treeCtrl;
    wxTextCtrl* _textCtrl;
    wxButton* _button;
    NodeModel* _nodeModel;
    Node* _root;
    string _currentPath;
    string _rootPath;

    // 初始化樹
    void initialize() {
        _root = _nodeModel->getRootNode();
        wxTreeItemId rootId = _treeCtrl->AddRoot(wxString(_root->name() + ", " + to_string(_root->size())));
        NodeIterator* nodeIterator = _root->createIterator();
        for (nodeIterator->first(); !nodeIterator->isDone(); nodeIterator->next())
            appendItem(rootId, nodeIterator->currentItem());
        _treeCtrl->ExpandAllChildren(rootId);
    }

    // 建立左方檔案樹
    void appendItem(wxTreeItemId parentId, Node* node) {
        wxTreeItemId nodeId = _treeCtrl->AppendItem(parentId, wxString(node->name() + ", " + to_string(node->size())));
        NodeIterator* iterator = node->createIterator();
        for (iterator->first(); !iterator->isDone(); iterator->next())
            appendItem(nodeId, iterator->currentItem());
    }

    // 取得目前檔案路徑
    string appendPath(wxTreeItemId nodeId) {
        string path = "";
        path += Node::split(_treeCtrl->GetItemText(nodeId).ToStdString(), ",")[0];
        if (_treeCtrl->GetItemParent(nodeId) != nullptr)
            path = appendPath(_treeCtrl->GetItemParent(nodeId)) + "/" + path;
        return path;
    }

    // 修改檔名
    int renameFile(wxTreeItemId oldNodeId, string newNodeName) {
        string oldNodePath = appendPath(oldNodeId);
        string newNodePath = "";
        vector<string> splitResult = Node::split(oldNodePath, "/");
        for (vector<string>::iterator iter = splitResult.begin(); iter != splitResult.end() - 1; iter++)
            newNodePath += *iter + "/";
        newNodePath += Node::split(newNodeName, ",")[0];
        return rename(oldNodePath.c_str(), newNodePath.c_str());
    }

    DECLARE_EVENT_TABLE()
};

BEGIN_EVENT_TABLE(TreeFrame, wxFrame)
// 設定事件的handler函式
EVT_TREE_ITEM_ACTIVATED(wxID_ANY, TreeFrame::onClick)
EVT_TREE_END_LABEL_EDIT(wxID_ANY, TreeFrame::onEdit)
EVT_BUTTON(wxID_BUTTON, TreeFrame::onSave)
END_EVENT_TABLE()

#endif
