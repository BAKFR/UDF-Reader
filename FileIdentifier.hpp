
#pragma once

#include "Descriptor.hpp"
#include "Tag.hpp"
#include "DString.hpp"

class FileIdentifier : public Descriptor
{
protected:
  charspec		charset;
  uint32_t		length;

  uint16_t		version;
  uint8_t		charasteristics;
  uint8_t		length_file_id;
  long_ad		ICB;
  uint16_t		length_impl_use;
  uint8_t		*impl_use;
  DString		file_id;
public:
  FileIdentifier(uint8_t *buffer, uint32_t length, charspec charset);

  void	setData(uint8_t *buffer);
  std::string  toString() const;

  FileIdentifier		*getNextFID(uint8_t *buffer) const;
  uint32_t		getSize() const;
};
