#ifndef TREE_TEST_CPP
#define TREE_TEST_CPP
#include <wx/wx.h>
#include "tree_test.h"
#include "tree_frame.h"

IMPLEMENT_APP(TreeTestApp)

bool TreeTestApp::OnInit() {
    // ®Ú¥Ø¿ý¦WºÙ
    string rootPath = wxApp::argv[1].ToStdString();
    wxFrame* frame = new TreeFrame(wxT("***Tree Test***"), rootPath);
    frame->Show(true);
    this->SetTopWindow(frame);
    return true;
}

#endif