#include <gtest/gtest.h>

#include "../src/node.h"
#include "../src/file.h"
#include "../src/folder.h"
#include <algorithm>

using namespace std;

// Test 

TEST (NodeTest, checkPath)
{
  // check if it is exist
  try {
    Node * not_exist = new File("test/test_folder/asdf.txt");
  }catch (string exception) {
      ASSERT_EQ(string("Node is not exist!"), exception);
  }
  // check if it is file
  try {
    Node * a_out = new File("test/test_folder");
  } catch (string exception) {
      ASSERT_EQ(string("It is not File!"), exception);
  }
  // check if it is folder
  try {
    Node * a_out = new Folder("test/test_folder/hello.txt");
  } catch (string exception) {
      ASSERT_EQ(string("It is not Folder!"), exception);
  }
}
TEST (NodeTest, Name)
{
  Node* file = new File("test/test_folder/hello.txt");
  ASSERT_EQ("hello.txt", file->name());
  Node* folder = new Folder("test/test_folder");
  ASSERT_EQ("test_folder", folder->name());
}
TEST (NodeTest ,findNode)
{
  Node* hello_txt = new File("test/test_folder/hello.txt");
  ASSERT_EQ("hello.txt",hello_txt->findNode("hello.txt"));

  Node* test_folder = new Folder("test/test_folder");
  Node* folder = new Folder("test/test_folder/folder");
  // //  Node* hello_txt = new File("test/test_folder/hello.txt");
  Node* folder_hello_txt = new File("test/test_folder/folder/hello.txt");
  test_folder->addChild(hello_txt);
  test_folder->addChild(folder);
  folder->addChild(folder_hello_txt);
  // //test_folder->addChild(folder_hello_txt);
  ASSERT_EQ("./hello.txt\n./folder/hello.txt", test_folder->findNode("hello.txt"));
}
TEST (NodeTest ,listNode)
{
  // file
  try {
    Node* file = new File("test/test_folder/hello.txt");
    file->listNode();
  }catch (string exception) {
      ASSERT_EQ(string("Not a directory"), exception);
  }
  // folder
  Node* test_folder_listNode = new Folder("test/test_folder");
  Node* folder_listNode = new Folder("test/test_folder/folder");
  Node* hello_txt_listNode = new File("test/test_folder/hello.txt");
  test_folder_listNode->addChild(folder_listNode);
  test_folder_listNode->addChild(hello_txt_listNode);
  ASSERT_EQ("folder hello.txt", test_folder_listNode->listNode());
}
