#include "LogicalVolumeDescriptor.hpp"
#include <cstring>
#include <iostream>
#include <sstream>


LogicalVolumeDescriptor:: LogicalVolumeDescriptor(const Tag &tag)
  : tag(tag)
{

}


LogicalVolumeDescriptor *LogicalVolumeDescriptor::loadFromFd(const Tag &tag, int fd) {
  LogicalVolumeDescriptor *lvd = new LogicalVolumeDescriptor(tag);
  uint8_t buffer[474];

  if (read(fd, buffer, 474) != 474) {
	std::cerr << "Error: Unable to read Logical Volume Descriptor" << std::endl;
	return NULL;
  }

  lvd->setData(buffer);
  return lvd;
}

void LogicalVolumeDescriptor::setData(uint8_t *buffer) {
  volumeDescriptorSequenceNumber = ((uint32_t *)buffer)[0];
  descriptorCharacterSet.setData(buffer);
  buffer+=64;
  memcpy(logicalVolumeIdentifier, buffer, 128);
  buffer+=128;
  logicalBlockSize = ((uint32_t *)buffer)[0];
  buffer+=sizeof(uint32_t);
  domainIdentifier.setData(buffer);
  buffer+=32;
  memcpy(logicalVolumeContentsUse, buffer, 16);
  buffer+=16;
  mapTableLength = ((uint32_t *)buffer)[0];
  buffer+=sizeof(uint32_t);
  numberOfPartitionMaps = ((uint32_t *)buffer)[0];
  buffer+=sizeof(uint32_t);
  implementationIdentifier.setData(buffer);
  buffer+=32;
  memcpy(implementationUse, buffer, 128);
  buffer+=128;
  integritySequenceExtent.setData(buffer);
  buffer+=8;
  partitionMap = new uint8_t[mapTableLength];
}

std::string LogicalVolumeDescriptor::toString() const {
  std::ostringstream oss;

  oss.flags(std::ios_base::boolalpha);

  oss << "==== Logical Volume Descriptor ====\n"
	  << tag.toString() << "--------------\n"
	  << "Volume descriptor sequence number : "
	  << volumeDescriptorSequenceNumber << "\n"
	  << "Descriptor Charset: " << descriptorCharacterSet.toString() << "\n"
	  << "Logical volume identifier : `" << logicalVolumeIdentifier 
	  << "`\n" << std::endl;
  oss<<"Logical block size : "<<logicalBlockSize<<std::endl;
  //oss<<"Domain identifier : "<<domainIdentifier.toString()<<std::endl;
  oss<<"Logical volume Contents use : "<<logicalVolumeContentsUse<<std::endl;
  oss<<"Map table length : "<<mapTableLength<<std::endl;
  oss<<"Number of partition maps : "<<numberOfPartitionMaps<<std::endl;
  //oss<<"Implementation identifier : "<<implementationIdentifier<<std::endl;
  oss<<"Implementation use : "<<implementationUse<<std::endl;
  oss<<"Integrity sequence extent : "<<integritySequenceExtent.toString()<<std::endl;
  return oss.str();
}
