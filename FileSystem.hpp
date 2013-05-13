
#pragma once

#include "Tag.hpp"

class FileSetDesc;

class FileSystem {
private:
  bool			debug;

  extend_ad		location;
  int			block_size;
  int			fd;

  FileSetDesc	*root;

  template<typename T>
  T *loadDescriptor(Tag::Type type);
public:
  FileSystem(const extend_ad &from, int block_size, int fd);
  Tag	getTagSector(int);
  bool	goTo(uint32_t sector);

  bool	loadRoot();
  bool	loadFirstDir();
};
