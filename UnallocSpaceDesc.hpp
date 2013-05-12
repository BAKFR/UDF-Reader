
#pragma once

#include "Tag.hpp"
#include "Descriptor.hpp"

class UnallocSpaceDesc : public Descriptor {
private:
  uint32_t		seq_number;
  uint32_t		nb_alloc_descs;
  extend_ad		*alloc_descs;
public:
  UnallocSpaceDesc();
  void	setData(uint8_t *buffer);
  std::string  toString() const;
  int	getNbAllocDescs() const;
  void	loadAllocationDescs(uint8_t *buffer);

  long double getFreeSpace() const;
};
