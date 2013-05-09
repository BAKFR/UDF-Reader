#pragma once

#include "Tag.hpp"
#include <cstdint>

struct EntityID {
  uint8_t flags;
  uint8_t identifier[23];
  uint8_t identifierSuffix[8];
  void setData(uint8_t *buffer);
  std::string toString();
};

class PartitionDescriptor {
protected:
  Tag descriptorTag;
  uint32_t volumeDescriptorSequenceNumber;
  uint16_t partitionFlags;
  uint16_t partitionNumber;
  EntityID partitionContent;
  uint8_t partitionContentsUse[128];
  uint32_t accessType;
  uint32_t partitionStartingLocation;
  uint32_t partitionLength;
  EntityID implementationIdentifier;
  uint8_t implementationUse[128];
  uint8_t reserved[156]; 
public:
  void setData(uint8_t *buffer);
  std::string toString() const;
};
