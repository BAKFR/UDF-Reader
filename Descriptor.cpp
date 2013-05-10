
#include "Descriptor.hpp"
#include <sstream>

Descriptor::Descriptor(const std::string &name, size_t size)
  : name(name), size(size), tag(0)
{
  
}

bool	Descriptor::loadFromFd(const Tag &tag, int fd)
{
  uint8_t *buffer = new uint8_t[size];

  if (read(fd, buffer, size - 16) != (int)size - 16) {
	std::cerr << "Error: Unable to read " << name << std::endl;
	delete[] buffer;
	return false;
  }
  this->tag = tag;
  this->setData(buffer);

  delete[] buffer;
  return true;
}

std::string		Descriptor::toString() const
{
  std::ostringstream oss;

  oss << "==== " << name << " ====\n"
	  << tag.toString() << "--------------\n";

  return oss.str();
}

const std::string		&Descriptor::getName() const
{
  return name;
}
