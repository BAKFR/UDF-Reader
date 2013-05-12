#include "CommandParser.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
  FileSystemTree fst;
  CommandParser parser;
  std::string line;
  
  while (1) {
  std::getline(std::cin, line);
  Command *cmd = parser.parse(line);
  if (cmd != NULL) {
    parser.execute(fst, *cmd);
    } else {
       std::cout<<"Invalid command."<<std::endl;
    }
  }
  return 0;
}
