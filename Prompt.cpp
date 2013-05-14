#include "Prompt.hpp"
#include "Command.hpp"
#include "UDF.hpp"
#include "FileSystem.hpp"
#include <string>
#include <iostream>
#include <cstdlib>
#include <fcntl.h>

void Prompt::displayArguments(Command *cmd) {
  unsigned int nb_arguments = cmd->getArgumentNumber();
  unsigned int i = 0;
  std::string arg;

  while (i < nb_arguments) {
    arg = cmd->getArgument(i);
    std::cout<<"Argument "<<i<<" = "<<arg<<std::endl;
    i++;
  }
}

Prompt::Prompt(int argc, char **argv) {
  promptPath = "$>";
  if (argc < 2) {
    std::cout<<"Usage: ./udf fileToParse"<<std::endl;
    exit(0);
  }
  fd = open(argv[1], O_RDONLY);

  if (fd < 2) {
    std::cout<<"Unable to open UDF volume "<<argv[0]<<std::endl;
    exit(0);
  }

  udf = new UDF(fd);
  if (!udf->isValid()) {
    std::cout<<argv[1]<<" is not a valid UDF volume."<<std::endl;
    exit(0);
  }

  i = udf->loadInfo();
  fs = new FileSystem(udf->getPartition(), udf->getSizeBlock(), fd);
  fs->loadFirstDir();
}

void Prompt::run() {
  std::string line;

  while (1) {
    std::cout<<promptPath;
    std::getline(std::cin, line);
    Command *cmd = parser.parse(line);
    if (cmd != NULL) {
      cmd->setUDFInfo(i);
      displayArguments(cmd);
      parser.execute(*fs, cmd, udf);
      delete cmd;
    }
  }
}
