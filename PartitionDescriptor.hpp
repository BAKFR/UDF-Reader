#pragma once

#include "Tag.hpp"
#include <cstdint>

class PartitionDescriptor {
protected:
  Tag descriptorTag;
  uint32_t volumeDescriptorSequenceNumber;
  uint16_t partitionFlags;
  uint16_t partitionNumber;
  regid partitionContent;
  uint8_t partitionContentsUse[129];
  uint32_t accessType;
  uint32_t partitionStartingLocation;
  uint32_t partitionLength;
  regid implementationIdentifier;
  uint8_t implementationUse[129];

  PartitionDescriptor(const Tag &tag);
public:
  void setData(uint8_t *buffer);
  std::string toString() const;
  static PartitionDescriptor *loadFromFd(const Tag &tag, int fd);
};
