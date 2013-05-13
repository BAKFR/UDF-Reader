
#pragma once

#include "Tag.hpp"

struct ICBTag {
  
  uint32_t		nb_prior_direct_entries;
  uint16_t		strategy_type;
  uint8_t		strategy_args[2];
  uint16_t		max_nb_entries;
  uint8_t		file_type;
  lb_addr		parent_ICB;
  uint16_t		flags;

  void setData(uint8_t *buffer);
  std::string toString() const;
};
