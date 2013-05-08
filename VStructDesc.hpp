
#pragma once

#include <iostream>

class VStructDesc
{
  char			type;
  char			id[6];
  char			version;
  char		   	data[2041];

 public:

  bool	isBEA() const;
  bool	isTEA() const;

  std::string toString() const;

  static VStructDesc *readFromFd(int fd);
  static bool checkIsUDF(int fd);

  static const int SECTOR_SIZE = 2048;
  static const int MAX_DESCRIPTOR_READ = 16;
};
