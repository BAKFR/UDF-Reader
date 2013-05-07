#include "PartitionDescriptor.hpp"
#include <cstring>

void EntityID::setData(uint8_t *buffer) {
  flags = ((uint8_t*)buffer)[0];
  buffer+=sizeof(uint8_t);
  memcpy(identifier, buffer, 23);
  buffer+=23;
  memcpy(identifierSuffix, buffer, 8);
}


void PartitionDescriptor::setData(uint8_t *buffer) {
  descriptorTag.setData(buffer);
  buffer+=sizeof(descriptorTag);
  volumeDescriptorSequenceNumber = ((uint32_t*)buffer)[0];
  buffer+=sizeof(uint32_t);
  partitionFlags = ((uint16_t*)buffer)[0];
  buffer+=sizeof(uint16_t);
  partitionNumber = ((uint16_t*)buffer)[0];
  buffer+=sizeof(uint16_t);
  partitionContent.setData(buffer);
  buffer+=sizeof(partitionContent);
  memcpy(partitionContentsUse, buffer, 128);
  buffer+=128;
  accessType = ((uint32_t*)buffer)[0];
  buffer+=sizeof(uint32_t);
  partitionStartingLocation = ((uint32_t*)buffer)[0];
  buffer+=sizeof(uint32_t);
  partitionLength = ((uint32_t*)buffer)[0];
  buffer+=sizeof(uint32_t);
  implementationIdentifier.setData(buffer);
  buffer+=sizeof(sizeof(implementationIdentifier));
  memcpy(implementationUse, buffer, 128);
}

std::string PartitionDescriptor::toString() const {
  std::cout<<"Volume descriptor sequence number : "<<volumeDescriptorSequenceNumber<<std::endl;
  std::cout<<"Partition flags : "<<partitionFlags<<std::endl;
  std::cout<<"Partition number : "<<partitionNumber<<std::endl;
  std::cout<<"Access type : "<<accessType<<std::endl;
  std::cout<<"Partition starting location : "<<partitionStartingLocation<<std::endl;
  std::cout<<"Partition length : "<<partitionLength<<std::endl;
  return "";
}
