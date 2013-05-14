#include "UDF.hpp"
#include "CommandCP.hpp"
#include "FileSystem.hpp"
#include <iostream>
#include <fcntl.h>

bool CommandCP::execute(FileSystem &fs, UDF& ) {

  int fd = open(arguments[1].c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);

  if (fd == -1) {
	std::cerr << "Error: unable to open file" << std::endl;
	return false;
  }

  if (!fs.copy(arguments[0], fd)) {
	return false;
  }

  std::cout << "Command CP executed." << std::endl;
  return true;
}
