
#pragma once

#include "Descriptor.hpp"
#include "ICBTag.hpp"

class FileSystem;
class FileIdentifier;

class FileEntry : public Descriptor
{
protected:
  charspec		charset;



  ICBTag		ICB_tag;

  uint32_t		Uid;
  uint32_t		Gid;
  uint32_t		Permissions;
  uint16_t		file_link_count;
  uint8_t		record_format;
  uint8_t		record_display_attributes;
  uint32_t		record_length;
  uint64_t		information_length;
  uint64_t		logical_block_recorded;
  Timestamp		access_time;
  Timestamp		modification_time;
  Timestamp		attribute_time;
  uint32_t		checkpoint;
  long_ad		ext_attr_ICB;
  //  EntityID		implementation_identifier;
  uint64_t		unique_id;
  uint32_t		length_ext_attrs;
  uint32_t		length_alloc_descs;

  short_ad		*alloc_descrs;

  FileIdentifier		*file_id;
public:
  FileEntry(const charspec &charset);

  void	setData(uint8_t *buffer);
  std::string  toString() const;

  uint32_t		getSizeAlloc();
  bool	loadAllocDescs(FileSystem &fs, int fd);
};
