#include "LogicalVolumeDescriptor.hpp"
#include <cstring>
#include <iostream>
#include <sstream>


LogicalVolumeDescriptor:: LogicalVolumeDescriptor()
  : Descriptor("Logical Volume Descriptor", 440)
{

}

void LogicalVolumeDescriptor::setData(uint8_t *buffer) {

  volumeDescriptorSequenceNumber = ((uint32_t *)buffer)[0];
  buffer += 4;
  descriptorCharacterSet.setData(buffer);
  buffer += 64;

  logicalVolumeIdentifier.setData(buffer, 128, &descriptorCharacterSet);

  buffer += 128;
  logicalBlockSize = ((uint32_t *)buffer)[0];
  buffer += 4;
  domainIdentifier.setData(buffer);
  buffer += 32;
  memcpy(logicalVolumeContentsUse, buffer, 16);
  buffer += 16;
  mapTableLength = ((uint32_t *)buffer)[0];
  buffer += 4;
  numberOfPartitionMaps = ((uint32_t *)buffer)[0];
  buffer += 4;
  implementationIdentifier.setData(buffer);
  buffer += 32;
  memcpy(implementationUse, buffer, 128);
  buffer += 128;
  integritySequenceExtent.setData(buffer);
  buffer += 8;
  partitionMaps = NULL;
}

std::string LogicalVolumeDescriptor::toString() const {
  std::ostringstream oss;

  oss.flags(std::ios_base::boolalpha);

  oss << Descriptor::toString()
	  << "Volume descriptor sequence number : "
	  << volumeDescriptorSequenceNumber << "\n"
	  << "Descriptor Charset: " << descriptorCharacterSet.toString() << "\n"
	  << "Logical volume identifier : " << logicalVolumeIdentifier.toString() << "\n"
	  << "Logical block size : " << logicalBlockSize << "\n"
	  << "Domain identifier : " << domainIdentifier.toString()
	  << "Logical volume Contents use : `"
	  << (char*) logicalVolumeContentsUse << "`\n"
	  << "Map table length : " << mapTableLength << " ("
	  << numberOfPartitionMaps << " partition maps)\n"
	  << "Implementation identifier : " << implementationIdentifier.toString()
	  << "Implementation use : `" << (char*) implementationUse << "`\n"
	  << "Integrity sequence extent : " << integritySequenceExtent.toString()
	  << "--------------\n"
	  << "Partition Maps : \n";

  for (uint32_t i = 0; i < numberOfPartitionMaps; i++) {
	oss << "N°" <<i << ": "<< partitionMaps[i].toString();
  }
  return oss.str();
}

int		LogicalVolumeDescriptor::getLengthPM() const
{
  return mapTableLength;
}

void	LogicalVolumeDescriptor::loadPartitionMaps(uint8_t *buffer)
{
  partitionMaps = new PartitionMap[numberOfPartitionMaps];
  for (uint32_t i = 0; i < numberOfPartitionMaps; i++)
	buffer += partitionMaps[i].setData(buffer);
}

int		LogicalVolumeDescriptor::PartitionMap::setData(uint8_t *buffer)
{
  type = buffer[0];
  length = buffer[1];
  memcpy(data, buffer + 2, length - 2);
  if (type == 1) {
	sequence_nbr = ((uint16_t*) data)[0];
	partition_nbr = ((uint16_t*) data)[1];
  }


  return length;
}

std::string		LogicalVolumeDescriptor::PartitionMap::toString() const
{
  std::ostringstream oss;

  oss << "partition map (Type: " << (int) type
	  << ", Length: " << (int)length << ")\n";
  if (type == 1)
	oss << "\tSequence: " << sequence_nbr << "\tPartition: " << partition_nbr << "\n";
  else
	oss << "\tData: `" << (char*)data << "`\n";

  return oss.str();
}

std::string		LogicalVolumeDescriptor::getVolumeID() const
{
  return logicalVolumeIdentifier.getRawString();
}

uint32_t		LogicalVolumeDescriptor::getBlockSize() const
{
  return logicalBlockSize;
}
