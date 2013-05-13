
#include "FileEntry.hpp"
#include <sstream>

FileEntry::FileEntry()
  : Descriptor("File Entry", 176)
{
}

void	FileEntry::setData(uint8_t *buffer)
{
  ICB_tag.setData(buffer);

  buffer += 96;
  ext_attr_ICB.setData(buffer);
}

std::string		FileEntry::toString() const {
  std::ostringstream oss;

  oss << Descriptor::toString()
	  << ICB_tag.toString()
	  << "...\n"
	  << "Extended Attribute ICB: "
	  << ext_attr_ICB.toString();

  return oss.str();
}
