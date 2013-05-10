#pragma once

#include "Descriptor.hpp"
#include <cstdint>


class PartitionDescriptor : public Descriptor {
protected:
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

public:
  PartitionDescriptor();
  void setData(uint8_t *buffer);
  std::string toString() const;
  uint32_t		getPartitionLength() const;
};
