
#pragma once

#include "Descriptor.hpp"
#include "ICBTag.hpp"

class FileEntry : public Descriptor
{
protected:
  ICBTag		ICB_tag;

  long_ad		ext_attr_ICB;

public:
  FileEntry();

  void	setData(uint8_t *buffer);
  std::string  toString() const;
};
