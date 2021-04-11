#ifndef UT_FS_H
#define UT_FS_H

#include <sys/stat.h>
#include <string>
#include "../src/visitor.h"
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/link.h"
#include "../src/node.h"
#include "../src/iterator.h"
#include "../src/null_iterator.h"
#include "../src/find_visitor.h"
#include "../src/update_path_visitor.h"


using namespace std;

class FileSystemTest : public ::testing::Test{
protected:
  void SetUp()
  {
    hello_txt = new File("test/test_folder/hello.txt");
    a_out = new File("test/test_folder/hw/a.out");
    hello_txt_Visitor = new FindVisitor("hello.txt");
    a_out_Visitor = new FindVisitor("a.out");
    test_folder = new Folder("test/test_folder");
    findVisitor = new FindVisitor("test_folder");
    hw = new Folder("test/test_folder/hw");
    hello_txt2 = new File("test/test_folder/hw/hello.txt");
    findVisitor2 = new FindVisitor("hello.txt");
    upv = new UpdatePathVisitor();
  }
  void TearDown()
  {
    delete hello_txt;
    delete a_out;
    delete hello_txt_Visitor;
    delete a_out_Visitor;
    delete test_folder;
    delete findVisitor;
    delete hw;
    delete hello_txt2;
    delete findVisitor2;
  }
  Node* test_folder;
  Node* hw;
  Node* hello_txt2;
  Node* hello_txt;
  Node* a_out;
  Visitor* findVisitor;
  Visitor* hello_txt_Visitor;
  Visitor* a_out_Visitor;
  Visitor* findVisitor2;
  UpdatePathVisitor * upv;
};


TEST_F(FileSystemTest, FindFileVisitor)
{
  hello_txt->accept(hello_txt_Visitor);
  ASSERT_EQ("hello.txt", hello_txt_Visitor->findResult());
  a_out->accept(a_out_Visitor);
  ASSERT_EQ("a.out", a_out_Visitor->findResult());
}

TEST_F(FileSystemTest,FolderFindItself)
{
  test_folder->accept(findVisitor);
  ASSERT_EQ("", findVisitor->findResult());
}

TEST_F(FileSystemTest, FindMultiPath)
{
  test_folder->addChild(hello_txt);
  test_folder->accept(hello_txt_Visitor);
  ASSERT_EQ("./hello.txt", hello_txt_Visitor->findResult());
  test_folder->addChild(hw);
  hw->addChild(hello_txt2);
  test_folder->accept(findVisitor2);
  ASSERT_EQ("./hello.txt\n./hw/hello.txt", findVisitor2->findResult());
}

TEST_F(FileSystemTest, NodeTypeError)
{
  ASSERT_ANY_THROW(new File("./123")); //If the node doesn't exist, you should throw string "Node is not exist!"
  ASSERT_ANY_THROW(new File("./test_folder/hw")); //If the File doesn't exist, you should throw string "It is not File!"
  ASSERT_ANY_THROW(new Folder("./test_folder/hello")); //If the Folder doesn't exist, you should throw string "It is not Folder!"
  ASSERT_ANY_THROW(new Link("./test_folder/hello.txt",hello_txt)); //If the Link doesn't exist, you should throw string "It is not Link!"
}

TEST_F(FileSystemTest , rename){
  Node* mk1 = new File("test/test_folder/hw/mk11");
  mk1->renameNode("mk1");
  ASSERT_EQ("mk1", mk1->getName());
  ASSERT_EQ("test/test_folder/hw/mk1",mk1->getPath());
  mk1->accept(upv);
  ASSERT_EQ("mk1", mk1->getName());
  ASSERT_EQ("test/test_folder/hw/mk1",mk1->getPath());
  mk1->renameNode("mk11");
  ASSERT_EQ("mk11", mk1->getName());
  ASSERT_EQ("test/test_folder/hw/mk11",mk1->getPath());
}

TEST_F(FileSystemTest, updatePath)
{
  struct stat _st;
  test_folder->addChild(hw);
  hw->addChild(a_out);
  hw->addChild(hello_txt2);
  hw->renameNode("TA_folder");
  ASSERT_EQ("TA_folder", hw->getName()); // Check the node name in your own file system!
  
  test_folder->accept(upv); 
 
  ASSERT_EQ("test/test_folder/TA_folder", hw->getPath()); // Check the path of itself!
  // ASSERT_EQ("test/test_folder/TA_folder/a.out", a_out->getPath()); // Check the path of child node!
  
  if (lstat("test/test_folder/TA_folder", &_st) != 0)
     FAIL(); // Check the physical node name!

  a_out->renameNode("a.txt");
  ASSERT_EQ("a.txt", a_out->getName()); // Check the node name in your own file system!
  
  a_out->accept(upv); 
  ASSERT_EQ("test/test_folder/TA_folder", hw->getPath()); // Check the path of itself!
  // ASSERT_EQ("test/test_folder/TA_folder/a.txt", a_out->getPath()); // Check the path of child node!
  
  // if (lstat("test/test_folder/TA_folder/a.txt", &_st) != 0)
  //    FAIL(); // Check the physical node name!
  hw->renameNode("hw");
  ASSERT_EQ("hw", hw->getName());
  test_folder->accept(upv); 
  a_out->renameNode("a.out");
  ASSERT_EQ("a.out", a_out->getName());
  a_out->accept(upv); 
}






#endif