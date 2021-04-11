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
#include "../src/filesystem_builder.h"


using namespace std;

// class FileSystemTest : public ::testing::Test{
// protected:
//   void SetUp()
//   {
//     hello_txt = new File("test/test_folder/hello.txt");
//     a_out = new File("test/test_folder/hw/a.out");
//     test_folder = new Folder("test/test_folder");
//     hw = new Folder("test/test_folder/hw");
//     hello_txt2 = new File("test/test_folder/hw/hello.txt");
//     ni = new NullIterator();
//     fb = FileSystemBuilder::instance();
//   }
//   void TearDown()
//   {
//     delete hello_txt;
//     delete a_out;
//     delete test_folder;
//     delete hw;
//     delete hello_txt2;
//     delete ni;
//     delete fb;
//   }
//   Node* test_folder;
//   Node* hw;
//   Node* hello_txt2;
//   Node* hello_txt;
//   Node* a_out;
//   Iterator * ni;
//   FileSystemBuilder * fb;
// };


// TEST_F(FileSystemTest, iterator)
// {
//   try {
//     ni->first();
//   }catch(string s){
//     ASSERT_EQ("No child member!",s);
//   }
//   try {
//     ni->next();
//   }catch(string s){
//     ASSERT_EQ("No child member!",s);
//   }
// } 

// TEST_F(FileSystemTest, filesystem_builder){
//   fb->build("test/test_folder/a.out");
//   ASSERT_EQ("a.out", fb->getRoot()->name());
//   ASSERT_EQ("test/test_folder/a.out", fb->getRoot()->getPath());
// }

// TEST_F(FileSystemTest, NodeTypeError)
// {
//   ASSERT_ANY_THROW(new File("./123")); //If the node doesn't exist, you should throw string "Node is not exist!"
//   ASSERT_ANY_THROW(new File("./test_folder/hw")); //If the File doesn't exist, you should throw string "It is not File!"
//   ASSERT_ANY_THROW(new Folder("./test_folder/hello")); //If the Folder doesn't exist, you should throw string "It is not Folder!"
//   ASSERT_ANY_THROW(new Link("./test_folder/hello.txt",hello_txt)); //If the Link doesn't exist, you should throw string "It is not Link!"
// }

// TEST_F(FileSystemTest , rename){
//   hello_txt->renameNode("hi.txt");
//   ASSERT_EQ("hi.txt", hello_txt->getName());
//   hello_txt->renameNode("hello.txt");
//   ASSERT_EQ("hello.txt", hello_txt->getName());
// }
TEST(test,123){
  
}
#endif