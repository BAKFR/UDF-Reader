
#include "FileIdentifier.hpp"
#include <sstream>

FileIdentifier::FileIdentifier(uint8_t *buffer, charspec charset)
  : Descriptor("File Identifier", 512), charset(charset)
{
  tag.setData(buffer);
  setData(buffer + 16);
}

void	FileIdentifier::setData(uint8_t *buffer)
{
  version = *(uint16_t*)buffer;
  buffer += 2;
  charasteristics = buffer[0];
  buffer++;
  length_file_id = buffer[0];
  buffer++;
  ICB.setData(buffer);
  buffer += 16;
  length_impl_use = *(uint16_t*)buffer;
  buffer += 2;
  impl_use = new uint8_t[length_impl_use];
  buffer += length_impl_use;
  file_id.setData(buffer, length_file_id, &charset);
}

std::string	    FileIdentifier::toString() const {
  std::ostringstream oss;

  oss << Descriptor::toString()
	  << "Version: " << (int)version << "\n"
	  << "Charasteristics: " << (int) charasteristics << "\n"
	  << "ICB: " << ICB.toString()
	  << "length_impl_use: " << length_impl_use << "\n";
  if (length_impl_use)
	oss << "Implementation Use: `" << (char*)impl_use << "`\n";
  oss << "Length File Id: " << (int)length_file_id << "\n";
  if (length_file_id)
	oss << "File ID: " << file_id.toString() << "\n";
  return oss.str();
}
