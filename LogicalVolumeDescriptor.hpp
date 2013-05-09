#pragma once

#include "Tag.hpp"
#include "PartitionDescriptor.hpp"
#include <cstdint>
#include <string>

struct charspec {
  uint8_t characterSetType;
  uint8_t characterSetInfo[63];
  void setData(uint8_t *buffer);
  std::string toString() const;
};

class LogicalVolumeDescriptor {
protected:
  Tag descriptorTag;
  uint32_t volumeDescriptorSequenceNumber;
  struct charspec descriptorCharacterSet;
  uint8_t logicalVolumeIdentifier[128];
  uint32_t logicalBlockSize;
  struct EntityID domainIdentifier;
  uint8_t logicalVolumeContentsUse[16];
  uint32_t mapTableLength;
  uint32_t numberOfPartitionMaps;
  struct EntityID implementationIdentifier;
  uint8_t implementationUse[128];
  struct extend_ad integritySequenceExtent;
  uint8_t *partitionMap;
public:
  void setData(uint8_t *buffer);
  std::string toString() const;
};
