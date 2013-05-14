
#include "FileEntry.hpp"
#include "FileSystem.hpp"
#include "FileIdentifier.hpp"
#include <sstream>
#include <memory>

FileEntry::FileEntry(const charspec &charset)
  : Descriptor("File Entry", 176), charset(charset)
{
}

void	FileEntry::setData(uint8_t *buffer)
{
  ICB_tag.setData(buffer);
 
  buffer += 20;
  Uid = ((uint32_t*) buffer)[0];  
  buffer += 4;
  Gid = ((uint32_t*) buffer)[0];
  buffer += 4;
  Permissions = ((uint32_t*) buffer)[0];
  buffer += 4;
  file_link_count = ((uint16_t*) buffer)[0];
  buffer += 2;
  record_format = ((uint8_t*) buffer)[0];
  buffer += 1;
  record_display_attributes = ((uint8_t*) buffer)[0];
  buffer += 1;
  record_length = ((uint32_t*) buffer)[0];
  buffer += 4;
  information_length = ((uint64_t*) buffer)[0];
  buffer += 8;
  logical_block_recorded = ((uint64_t*) buffer)[0];
  buffer += 8;
  access_time = ((Timestamp*) buffer)[0];
  buffer += 12;
  modification_time = ((Timestamp*) buffer)[0];
  buffer += 12;
  attribute_time = ((Timestamp*) buffer)[0];
  buffer += 12;
  checkpoint = ((uint32_t*) buffer)[0];
  buffer += 4;
  ext_attr_ICB.setData(buffer);
  buffer += 48;
  unique_id = ((uint64_t*) buffer)[0];
  buffer += 8;
  length_ext_attrs = ((uint32_t*) buffer)[0];
  buffer += 4;
  length_alloc_descs = ((uint32_t*) buffer)[0];

  alloc_descrs = NULL;
}

bool	FileEntry::loadAllocDescs(FileSystem &fs, int fd) {
  int length = getSizeAlloc();

  uint8_t *buffer = new uint8_t[length];
  std::unique_ptr<uint8_t[]> ptrBuffer(buffer);

  if (read(fd, buffer, length) != length) {
	std::cerr << "Error: Unable to read alloc descriptors for FE" << std::endl;
	return false;
  }

  // TODO: HERE READ ATTRS
  buffer += length_ext_attrs;

  //Alloc Descriptors parsing
  alloc_descrs.reset(new short_ad[length_alloc_descs / 8]);
  for (uint32_t i = 0; i < length_alloc_descs / 8; i++) {
	alloc_descrs[i].setData(buffer);
	buffer += 8;

	if (!fs.goTo(alloc_descrs[i].position))
	  return false;


	std::unique_ptr<uint8_t[]> bufferAlloc(new uint8_t[alloc_descrs[i].length]);
	uint8_t		*currentPtr = bufferAlloc.get();

	if (read(fd, bufferAlloc.get(), alloc_descrs[i].length)
		!= alloc_descrs[i].length) {
	  return false;
	}

	auto *fi = new FileIdentifier(bufferAlloc.get(),
								  alloc_descrs[i].length, charset);
	while (fi != NULL) {
	  FIDs.push_back(fi);
	  currentPtr += fi->getSize();
	  fi = fi->getNextFID(currentPtr);
	}
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
	  << "Uid: " << Uid << "\n"
	  << "Gid: " << Gid << "\n"
	  << "Permissions: " << Permissions << "\n"
	  << "File Link Count: " << file_link_count << "\n"
	  << "Record Format: " << record_format << "\n"
	  << "Record Display Attributes: " << record_display_attributes << "\n"
	  << "Record Length: " << record_length << "\n"
	  << "Information Length: " << information_length << "\n"
	  << "Logical Block Recorded: " << logical_block_recorded << "\n"
    	  << "Access Time: " << access_time.toString() << "\n"
	  << "Modification Time: " << modification_time.toString() << "\n"
	  << "Attribute Time: " << attribute_time.toString() << "\n"
	  << "Checkpoint: " << checkpoint << "\n"
	  << "Extended Attribute ICB: "
	  << ext_attr_ICB.toString()
	  << "Length Extended Attributes: " << length_ext_attrs << "\n"
	  << "Length Allocation Descriptors: " << length_alloc_descs << "\n"
	  << "Allocation Descriptors:\n";
  for (uint32_t i = 0; i < length_alloc_descs / 8; i++) {
	oss << "\t" << alloc_descrs[i].toString() << "\n";
  }
  if (FIDs.size()) {
	oss << "--> Alloc Descriptors:\n";
	int i = 0;
	for (auto it = FIDs.begin(); it != FIDs.end(); ++it, ++i) {
	  oss << "***FID N° " << i << "***\n";
	  oss << (*it)->toString();
	}
  }
  return oss.str();
}
