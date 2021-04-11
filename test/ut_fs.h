#ifndef UT_FS_H
#define UT_FS_H

#include <sys/stat.h>
#include <string>
#include "../src/file.h"
#include "../src/folder.h"
#include "../src/node.h"
#include "../src/utilities.h"
#include "../src/iterator.h"
#include "../src/null_iterator.h"

using namespace std;

class NodeTest : public ::testing::Test{
protected:
  void SetUp()
  {
    hw = new Folder("test/test_folder/hw");
    a_out = new File("test/test_folder/hw/a.out");
    hw1_cpp = new File("test/test_folder/hw/hw1.cpp");
    hello_txt= new File("test/test_folder/hello.txt");
    test_folder= new Folder("test/test_folder");
    hw->addChild(a_out);
    hw->addChild(hw1_cpp);
    test_folder->addChild(hello_txt);
    test_folder->addChild(hw);
    u = new Utilities();
  }
  void TearDown()
  {
    delete hw;
    delete a_out;
    delete hw1_cpp;
    delete hello_txt;
    delete test_folder;
    delete u;
  }
  Folder* hw;
  Node* a_out;
  Node* hw1_cpp;
  File* hello_txt;
  Node* test_folder;
  Utilities* u;
};

TEST_F(NodeTest, First) {
  ASSERT_EQ(14, hello_txt->size());
}

// TEST_F(NodeTest, Second) {
//   Iterator * it= test_folder->createIterator();
//   // ASSERT_EQ(128, test_folder->size());
//   it->first();
//   ASSERT_EQ(14, it->currentItem()->size());
//   it->next();
//   ASSERT_EQ(128, it->currentItem()->size());
// }

TEST_F(NodeTest, CatchException){
  try{
    hello_txt->addChild(test_folder);
    ASSERT_EQ(true, false);
  } catch(string s){
    ASSERT_EQ("Invalid add!", s);
  }
}

TEST_F(NodeTest, IteratorFromFileException) {
  try{
    Iterator * it = a_out->createIterator();
    it->first();
  }catch(string s){
    ASSERT_EQ("no child member",s);
  }

  try{
    Iterator * it = a_out->createIterator();
    it->next();
  }catch(string s){
    ASSERT_EQ("no child member",s);
  }

  try{
    Iterator * it = a_out->createIterator();
    it->currentItem();
  }catch(string s){
    ASSERT_EQ("no child member",s);
  }
}

TEST_F(NodeTest, IteratorFromFolder) {
  Iterator * it = hw->createIterator();
  it->first(); // Initialize
  ASSERT_EQ(a_out, it->currentItem());
  it->next();
  ASSERT_EQ(hw1_cpp, it->currentItem());
  it->next();
  ASSERT_TRUE(it->isDone());
}

TEST_F(NodeTest, IteratorFromFolderCurrentItemException) {
  try{
    Iterator * it = hw->createIterator();
    it->first(); // Initialize
    ASSERT_EQ(a_out, it->currentItem());
    it->next();
    ASSERT_EQ(hw1_cpp, it->currentItem());
    it->next();
    ASSERT_TRUE(it->isDone());
    it->currentItem();
  }catch (string s){
    ASSERT_EQ("No current item!",s);
  }
}

TEST_F(NodeTest, IteratorFromFolderNextException) {
  try{
    Iterator * it = hw->createIterator();
    it->first(); // Initialize
    ASSERT_EQ(a_out, it->currentItem());
    it->next();
    ASSERT_EQ(hw1_cpp, it->currentItem());
    it->next();
    ASSERT_TRUE(it->isDone());
    it->next();
  }catch (string s){
    ASSERT_EQ("Moving past the end!",s);
  }
}

TEST_F(NodeTest, IteratorFromFile){
  Iterator* it= hello_txt->createIterator();
  ASSERT_TRUE(it->isDone());
}

TEST_F(NodeTest, listNode){
  // file
  try {
    u->listNode(hello_txt);
  }catch (string exception) {
    ASSERT_EQ(string("Not a directory"), exception);
  }

  // folder
  ASSERT_EQ("hello.txt hw", u->listNode(test_folder));
}

TEST_F(NodeTest,findNode)
{
  // file
  ASSERT_EQ("hello.txt",u->findNode(hello_txt,"hello.txt"));

  // folder
  ASSERT_EQ("./hw/a.out", u->findNode(test_folder,"a.out"));
}


#endif