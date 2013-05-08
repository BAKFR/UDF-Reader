
#pragma once

#include <cstdint>
#include <iostream>

struct Tag {
  
  enum Type {
	PrimaryVDesc = 1,
	AVDP,
	VDescPtr,
	ImplUseVDesc,
	PartitionDesc,
	LogicVDesc,
	UnallocSpDesc,
	TermDesc,
	LogicVIntergrityDesc
  };

  uint16_t	type;
  uint16_t  version;
  uint8_t	checksum;
  uint16_t  serial;
  uint16_t	CRC;
  uint16_t  CRC_length;
  uint32_t  location;

  uint32_t	real_location;
  
  Tag(uint32_t location);

  void		  setData(uint8_t *buffer);

  bool		  isChecksumOK() const;
  bool		  isLocationOK() const;
  bool		  isValid() const;
  std::string toString() const;
};

struct extend_ad {
  uint32_t	length;
  uint32_t	location;
  
  void		  setData(uint8_t *buffer);
  std::string toString() const;
};

struct regid {
  uint8_t		flags;
  bool			isDirty;
  bool			isProtected;
  uint8_t		id[24];
  uint8_t		suffix[9];

  void		  setData(uint8_t *buffer);
  std::string toString() const;
};
