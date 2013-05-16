#include "UDF.hpp"
#include <iostream>
#include "CommandDIR.hpp"
#include "FileSystem.hpp"

bool CommandDIR::execute(FileSystem &tree, UDF&) {
  auto infos = tree.getDirInfo();

  for (const FileIdentifier::InfoDir *info : infos) {
	uint64_t size = info->length;
	size /= 1024;
	const char *unit = "KB";

	if (size > 2000) {
	  size /= 1024;
	  unit = "MB";
	}
	if (size > 2000) {
	  size /= 1024;
	  unit = "GB";
	}

	if (info->hidden)
	  std::cout << "<hide>";
	std::cout << "\t" << info->name
			  << "\t\t\t";
	if (info->isDir)
	  std::cout << "<dir>";
	else {
	  std::cout.precision(3);
	  std::cout << size << unit;
	}
	std::cout << "\t" << info->date.toString() << std::endl;
  }
  std::cout << "Command dir executed." << std::endl;
  return true;
}
