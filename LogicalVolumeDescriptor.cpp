#include "LogicalVolumeDescriptor.hpp"
#include <cstring>
#include <iostream>
#include <sstream>

void charspec::setData(uint8_t *buffer) {
  characterSetType = ((uint8_t*)buffer)[0];
  buffer+=sizeof(uint8_t);
  memcpy(characterSetInfo, buffer, 63);
}

std::string charspec::toString() const {
  std::ostringstream oss;

  oss.flags(std::ios_base::boolalpha);
  oss<<"Character set type = "<<characterSetType<<std::endl;
  return oss.str();
}

void LogicalVolumeDescriptor::setData(uint8_t *buffer) {
  descriptorTag.setData(buffer);
  buffer+=16;
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

  descriptorTag.toString();  
  oss.flags(std::ios_base::boolalpha);
   oss<<"Volume descriptor sequence number : "<<volumeDescriptorSequenceNumber<<std::endl;
   descriptorCharacterSet.toString();
   oss<<"Logical volume identifier : "<<logicalVolumeIdentifier<<std::endl;
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
