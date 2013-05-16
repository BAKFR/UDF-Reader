
#include "FileIdentifier.hpp"
#include "FileSystem.hpp"
#include "FileEntry.hpp"

#include <sstream>
#include <cstring>

FileIdentifier::FileIdentifier(uint8_t *buffer, uint32_t length, charspec charset)
  : Descriptor("File Identifier", 512), charset(charset), length(length)
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
  impl_use = new uint8_t[length_impl_use + 1];
  memcpy(impl_use, buffer, length_impl_use);
  impl_use[length_impl_use] = '\0';
  buffer += length_impl_use;
  file_id.setData(buffer, length_file_id, &charset);
}

std::string	    FileIdentifier::toString() const {
  std::ostringstream oss;

  oss.flags(std::ios_base::boolalpha);
  oss << Descriptor::toString()
	  << "Version: " << (int)version << "\n"
	  << "Charasteristics: " << (int) charasteristics << "\n"
	  << "\tHidden ? " << isHidden()
	  << "; Directory ? " << isDirectory()
	  << "; Parent ? " << isParent()
	  << "\n"
	  << "ICB: " << ICB.toString()
	  << "length_impl_use: " << length_impl_use << "\n";
  if (length_impl_use)
	oss << "Implementation Use: `" << (char*)impl_use << "`\n";
  oss << "Length File Id: " << (int)length_file_id << "\n";
  if (length_file_id)
	oss << "File ID: " << file_id.toString() << "\n";
  return oss.str();
}

FileIdentifier	*FileIdentifier::getNextFID(uint8_t *buffer) const {
  uint32_t cur_size = getSize();

  if (length > cur_size)
	return new FileIdentifier(buffer, length - cur_size, charset);
  return NULL;
}

uint32_t		FileIdentifier::getSize() const {
  uint32_t		cur_size = length_file_id + length_impl_use + 38;

  return cur_size + (4 - (cur_size % 4) % 4);
}

bool			FileIdentifier::isHidden() const {
  return charasteristics & 0x1;
}

bool			FileIdentifier::isDirectory() const {
  return charasteristics & 0x2;
}

bool			FileIdentifier::isParent() const {
  return charasteristics & 0x8;
}

bool			FileIdentifier::isName(const std::string &name) const
{
  return (name == file_id.getRawString());
}

FileEntry		*FileIdentifier::loadTarget(FileSystem &fs, int fd)
{
  if (ICB.length != 0)
	return FileEntry::fullLoad(fs, ICB.location.block_nbr, fd);
  else
	return NULL;
}

FileIdentifier::InfoDir			*FileIdentifier::getInfoDir(FileSystem &fs, int fd)
{
  InfoDir	*tmp = new InfoDir();
  
  FileEntry *fe = loadTarget(fs, fd);

  tmp->hidden = isHidden();
  tmp->name = isParent() ? ".." : file_id.getRawString();
  tmp->isDir = isDirectory();
  tmp->length = fe->getLength();
  tmp->date = fe->getTime();
  delete fe;
  return tmp;
}
