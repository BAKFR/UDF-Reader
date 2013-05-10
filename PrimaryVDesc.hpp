
#pragma once

#include <iostream>
#include <cstdint>

#include "Tag.hpp"
#include "DString.hpp"

class PrimaryVDesc {
private:
  Tag	tag;

  uint32_t		VDS_number;
  uint32_t		number;
  DString		id;
  uint16_t		seq_number;
  uint16_t		max_seq_number;
  uint16_t		interchange_level;
  uint16_t		max_interchange_level;
  uint32_t		charset_list;
  uint32_t		max_charset_list;
  DString		set_id;
  charspec		desc_charset;
  charspec		expl_charset;
  extend_ad		vol_abstract;
  extend_ad		vol_copyright;
  regid			app_id;
  Timestamp		time;
  regid			impl_id;
  uint8_t		impl_use[64];
  uint32_t		previous_sequence;
  uint16_t		flags;

  PrimaryVDesc(const Tag &tag);

public:

  void	setData(uint8_t *buffer);
  static PrimaryVDesc *loadPVDFromFd(const Tag &tag, int fd);
  std::string  toString() const;
};
