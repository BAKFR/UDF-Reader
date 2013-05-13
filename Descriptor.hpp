
#pragma once

#include "Tag.hpp"
#include <string>

class Descriptor {
protected:
  std::string	name;
  size_t		size;

  Tag			tag;

  Descriptor(const std::string &name, size_t size);
public:

  virtual void	setData(uint8_t *buffer) = 0;
  bool	loadFromFd(const Tag &tag, int fd);
  std::string	toString() const;

  const std::string	&getName() const;
  virtual ~Descriptor(){}
};
