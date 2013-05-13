#include "Prompt.hpp"
#include "Command.hpp"
#include <string>
#include <iostream>

void Prompt::displayArguments(Command *cmd) {
  unsigned int nb_arguments = cmd->getArgumentNumber();
  int i = 0;
  std::string arg;

  while (i < nb_arguments) {
    arg = cmd->getArgument(i);
    std::cout<<"Argument "<<i<<" = "<<arg<<std::endl;
    i++;
  }
}

void Prompt::run() {
  std::string line;

  while (1) {
    std::getline(std::cin, line);
    Command *cmd = parser.parse(line);
    if (cmd != NULL) {
      displayArguments(cmd);
      parser.execute(fst, cmd, udf);
    }
  }
}
