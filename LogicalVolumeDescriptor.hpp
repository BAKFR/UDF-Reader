#pragma once

#include "Tag.hpp"
#include "Descriptor.hpp"
#include "DString.hpp"
#include <cstdint>
#include <string>

class LogicalVolumeDescriptor : public Descriptor {
public:

  struct PartitionMap {
	uint8_t		type;
	uint8_t		length;
	uint8_t		*data;
	uint16_t	sequence_nbr;
	uint16_t	partition_nbr;

	int setData(uint8_t *buffer);
	std::string toString() const;
  };

protected:

  uint32_t		volumeDescriptorSequenceNumber;
  charspec		descriptorCharacterSet;
  DString		logicalVolumeIdentifier;
  uint32_t		logicalBlockSize;
  regid			domainIdentifier;
  uint8_t		logicalVolumeContentsUse[16];
  uint32_t		mapTableLength;
  uint32_t		numberOfPartitionMaps;
  regid			implementationIdentifier;
  uint8_t		implementationUse[128];
  extend_ad		integritySequenceExtent;
  PartitionMap	*partitionMaps;

public:
  LogicalVolumeDescriptor();
  void setData(uint8_t *buffer);
  std::string toString() const;

  int getLengthPM() const;
  void	loadPartitionMaps(uint8_t *buffer);

  std::string	getVolumeID() const;
  uint32_t		getBlockSize() const;
};
