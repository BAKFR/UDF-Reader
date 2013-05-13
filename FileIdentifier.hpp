
#pragma once

#include "Descriptor.hpp"
#include "Tag.hpp"
#include "DString.hpp"

class FileIdentifier : public Descriptor
{
protected:
  charspec		charset;

  uint16_t		version;
  uint8_t		charasteristics;
  uint8_t		length_file_id;
  long_ad		ICB;
  uint16_t		length_impl_use;
  uint8_t		*impl_use;
  DString		file_id;
public:
  FileIdentifier(uint8_t *buffer, charspec charset);

  void	setData(uint8_t *buffer);
  std::string  toString() const;
};
