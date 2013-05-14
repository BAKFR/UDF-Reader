
#pragma once

#include "Descriptor.hpp"
#include "ICBTag.hpp"
#include <vector>
#include <memory>

class FileSystem;
class FileIdentifier;

class FileEntry : public Descriptor
{
protected:
  charspec		charset;



  ICBTag		ICB_tag;

  uint32_t		record_length;

  uint64_t		logical_block_recorded;

  long_ad		ext_attr_ICB;

  uint32_t		length_ext_attrs;
  uint32_t		length_alloc_descs;

  std::unique_ptr<short_ad[]>		alloc_descrs;

  std::vector<FileIdentifier*>		FIDs;
public:
  FileEntry(const charspec &charset);

  void	setData(uint8_t *buffer);
  std::string  toString() const;

  uint32_t		getSizeAlloc();
  bool	loadAllocDescs(FileSystem &fs, int fd);
};
