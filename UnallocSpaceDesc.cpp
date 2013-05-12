
#include <sstream>
#include <cstring>
#include <unistd.h>
#include "UnallocSpaceDesc.hpp"


UnallocSpaceDesc::UnallocSpaceDesc()
  : Descriptor("Unallocated Space Descriptor", 24)
{

}

void	UnallocSpaceDesc::setData(uint8_t *buffer) {
  seq_number = ((uint32_t*)buffer)[0];
  nb_alloc_descs = ((uint32_t*)buffer)[1];
  alloc_descs = NULL;
}

std::string  UnallocSpaceDesc::toString() const {
  std::ostringstream oss;

  oss << Descriptor::toString()
	  << "VDS number: " << seq_number << "\n"
	  << "Nb of allocation descriptor: " << nb_alloc_descs << "\n"
	  << "Allocation Descriptors:\n";
  for (uint32_t i = 0; i < nb_alloc_descs; i++)
	oss << alloc_descs[i].toString();
  return oss.str();
}

int	UnallocSpaceDesc::getNbAllocDescs() const {
  return nb_alloc_descs;
}

void	UnallocSpaceDesc::loadAllocationDescs(uint8_t *buffer) 
{
  alloc_descs = new extend_ad[nb_alloc_descs];

  for (uint32_t i = 0; i < nb_alloc_descs; i++, buffer += 8) {
	alloc_descs[i].setData(buffer);
  }
}

long double		UnallocSpaceDesc::getFreeSpace() const {
  long double ret = 0;
  for (uint32_t i = 0; i < nb_alloc_descs; i++)
	ret += alloc_descs[i].length;
  return ret;
}
