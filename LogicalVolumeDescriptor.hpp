#pragma once

#include "Tag.hpp"
#include "PartitionDescriptor.hpp"
#include <cstdint>
#include <string>

class LogicalVolumeDescriptor {
protected:
  Tag tag;

  uint32_t volumeDescriptorSequenceNumber;
  charspec descriptorCharacterSet;
  uint8_t logicalVolumeIdentifier[128];
  uint32_t logicalBlockSize;
  regid domainIdentifier;
  uint8_t logicalVolumeContentsUse[16];
  uint32_t mapTableLength;
  uint32_t numberOfPartitionMaps;
  regid implementationIdentifier;
  uint8_t implementationUse[128];
  extend_ad integritySequenceExtent;
  uint8_t *partitionMap;

  LogicalVolumeDescriptor(const Tag &tag);
public:
  void setData(uint8_t *buffer);
  std::string toString() const;
  static LogicalVolumeDescriptor *loadFromFd(const Tag &tag, int fd);
};
