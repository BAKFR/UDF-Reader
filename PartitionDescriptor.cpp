#include "PartitionDescriptor.hpp"
#include <cstring>
#include <string>
#include <sstream>

PartitionDescriptor::PartitionDescriptor(const Tag &tag)
  : descriptorTag(tag)
{
}

void PartitionDescriptor::setData(uint8_t *buffer) {
  volumeDescriptorSequenceNumber = ((uint32_t*)buffer)[0];
  buffer += 4;
  partitionFlags = ((uint16_t*)buffer)[0];
  buffer += 2;
  partitionNumber = ((uint16_t*)buffer)[0];
  buffer += 2;
  partitionContent.setData(buffer);
  buffer += 32;
  memcpy(partitionContentsUse, buffer, 128);
  partitionContentsUse[128] = '\0';
  buffer += 128;
  accessType = ((uint32_t*)buffer)[0];
  buffer += 4;
  partitionStartingLocation = ((uint32_t*)buffer)[0];
  buffer += 4;
  partitionLength = ((uint32_t*)buffer)[0];
  buffer += 4;
  implementationIdentifier.setData(buffer);
  buffer += 32;
  memcpy(implementationUse, buffer, 128);
  implementationUse[128] = '\0';
}

std::string PartitionDescriptor::toString() const {
  std::ostringstream oss;

  oss << "==== Partition Descriptor ====\n"
	  << descriptorTag.toString() << "-------------\n"
	  << "Volume descriptor sequence number : "
	  << volumeDescriptorSequenceNumber << "\n"
	  << "Partition flags : "<< partitionFlags << "\n"
	  << "Partition number : " << partitionNumber << "\n"
	  << "Partition Content: " << partitionContent.toString()
	  << "Partition Content USe: `" << partitionContentsUse << "`\n"
	  << "Access type : "<<accessType << "\n"
	  << "Partition Location : "<< partitionStartingLocation
	  << " (length : " << partitionLength << ")\n"
	  << "Implementation Id: " << implementationIdentifier.toString()
	  << "Implementation USe: `" << implementationUse << "`\n";
  return oss.str();
}

PartitionDescriptor *PartitionDescriptor::loadFromFd(const Tag &tag, int fd) {
  PartitionDescriptor *pd = new PartitionDescriptor(tag);
  uint8_t buffer[356];

  if (read(fd, buffer, 356) != 356) {
	std::cerr << "Error: Unable to read Partition Descriptor" << std::endl;
	return NULL;
  }

  pd->setData(buffer);
  return pd;
}
