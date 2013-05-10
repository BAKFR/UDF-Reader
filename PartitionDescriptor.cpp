#include "PartitionDescriptor.hpp"
#include <cstring>
#include <string>
#include <sstream>

PartitionDescriptor::PartitionDescriptor()
  : Descriptor("Partition Descriptor", 356)
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

  oss << Descriptor::toString()
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

uint32_t		PartitionDescriptor::getPartitionLength() const
{
  return partitionLength;
}
