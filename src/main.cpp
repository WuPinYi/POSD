#include "terminal.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std; 

// read file
string readFile(string fileName)
{
  fstream file;
  string input;
  ifstream inputFile(fileName);
  if (!inputFile.is_open()){}
  else
  {
    while(getline(inputFile,input))
    {
      return input;
    }
  }
}

void writeFile(string content)
{
  fstream file;
  file.open("output.txt",ios::out);
  if(!file)
  {
    cerr << "Can't open file!\n";
  }
  file << content;
  file.close();
}

int main(int argc, char *argv[]){
  // argv you can see makefile "bin/geo input.txt output.txt area inc"
  // argv[0] = input.txt, argv[1] = output.txt, argv[2] = area, argv[3] = inc 
  // implement reading input.txt
  // compose the string to Terminal(** Input string **)
  // **Input string**  Example: "Ellipse (6,5) Triangle (3,0,0,2,-3,0) CircularSector (8,40) area inc"
  // call showResult() to get result
  // write the result to output.txt
  // Don't hard code!!!
  
  if (argc != 5)
  {
    writeFile ("Unuseful User Input!");
  }else
  {
    Terminal* terminal = new Terminal(readFile(argv[1])+""+argv[3]+""+argv[4]);
    writeFile(terminal->showResult());
  }
}
