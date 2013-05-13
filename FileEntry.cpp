
#include "FileEntry.hpp"
#include "FileSystem.hpp"
#include "FileIdentifier.hpp"
#include <sstream>

FileEntry::FileEntry(const charspec &charset)
  : Descriptor("File Entry", 176), charset(charset)
{
}

void	FileEntry::setData(uint8_t *buffer)
{
  ICB_tag.setData(buffer);

  buffer += 36;
  record_length = ((uint32_t*) buffer)[0];

  buffer += 12;
  logical_block_recorded = ((uint64_t*) buffer)[0];

  buffer += 48;
  ext_attr_ICB.setData(buffer);

  buffer += 56;
  length_ext_attrs = ((uint32_t*) buffer)[0];
  buffer += 4;
  length_alloc_descs = ((uint32_t*) buffer)[0];

  alloc_descrs = NULL;
}

bool	FileEntry::loadAllocDescs(FileSystem &fs, int fd) {
  int length = getSizeAlloc();

  uint8_t *buffer = new uint8_t[length];
  if (read(fd, buffer, length) != length) {
	std::cerr << "Error: Unable to read alloc descriptors for FE" << std::endl;
	delete[] buffer;
	return false;
  }
  delete[] buffer;

  // TODO: HERE READ ATTRS
  buffer += length_ext_attrs;

  //Alloc Descriptors parsing
  alloc_descrs = new short_ad[length_alloc_descs / 8];
  for (uint32_t i = 0; i < length_alloc_descs / 8; i++) {
	alloc_descrs[i].setData(buffer);
	buffer += 8;
  }

  //Load of the first Allocation Descriptor (File Identifier)
  if (length_alloc_descs > 0) {
	if (!fs.goTo(alloc_descrs[0].position))
	  return false;

	buffer = new uint8_t[alloc_descrs[0].length];
	if (read(fd, buffer, alloc_descrs[0].length) != alloc_descrs[0].length) {
	  delete buffer;
	  return false;
	}

	file_id = new FileIdentifier(buffer, charset);
	
	delete buffer;
  }
  return true;
}

uint32_t		FileEntry::getSizeAlloc() {
  return length_alloc_descs + length_ext_attrs;
}

std::string		FileEntry::toString() const {
  std::ostringstream oss;

  oss << Descriptor::toString()
	  << ICB_tag.toString()
	  << "...\n"
	  << "Record Length: " << record_length << "\n"
	  << "...\n"
	  << "Logical Block Recorded: " << logical_block_recorded << "\n"
	  << "...\n"
	  << "Extended Attribute ICB: "
	  << ext_attr_ICB.toString()
	  << "Length Extended Attributes: " << length_ext_attrs << "\n"
	  << "Length Allocation Descriptors: " << length_alloc_descs << "\n"
	  << "Allocation Descriptors:\n";
  for (uint32_t i = 0; i < length_alloc_descs / 8; i++) {
	oss << "\t" << alloc_descrs[i].toString() << "\n";
  }
  if (file_id) {
	oss << "--> Alloc Descriptors:\n"
		<< file_id->toString();
  }
  return oss.str();
}
