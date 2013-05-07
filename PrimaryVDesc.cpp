
#include <sstream>
#include <cstring>
#include <unistd.h>
#include "PrimaryVDesc.hpp"

PrimaryVDesc::PrimaryVDesc(const Tag &tag)
  : tag(tag)
{

}

PrimaryVDesc *PrimaryVDesc::loadPVDFromFd(const Tag &tag, int fd) {
  PrimaryVDesc *pvd = new PrimaryVDesc(tag);
  uint8_t buffer[474];

  if (read(fd, buffer, 474) != 474) {
	std::cerr << "Error: Unable to read Primary Volume Descriptor" << std::endl;
	return NULL;
  }

  pvd->setData(buffer);
  return pvd;
}

void	PrimaryVDesc::setData(uint8_t *buffer) {

  VDS_number = ((uint32_t*) buffer)[0];
  number = ((uint32_t*) buffer)[1];
  memcpy(id, buffer + 8, 32);
  id[32] = '\0';
  seq_number = ((uint16_t*) (buffer + 40))[0];
  max_seq_number = ((uint16_t*) (buffer + 42))[0];
  interchange_level = ((uint16_t*) (buffer + 44))[0];
  max_interchange_level = ((uint16_t*) (buffer + 46))[0];
  charset_list = ((uint32_t*) (buffer + 48))[0];
  max_charset_list = ((uint32_t*) (buffer + 52))[0];
  memcpy(set_id, buffer + 56, 128);
  set_id[128] = '\0';
  //charsp
  //charsp
  vol_abstract.setData(buffer + 312);
  vol_copyright.setData(buffer + 320);
  app_id.setData(buffer + 328);
  //timestamp
  impl_id.setData(buffer + 372);
  memcpy(impl_use, buffer + 404, 64);
  previous_sequence = ((uint32_t*) (buffer + 468))[0];
  flags = ((uint16_t*) (buffer + 472))[0];
}

std::string  PrimaryVDesc::toString() const {
  std::ostringstream oss;

  oss << "==== Primary Volume Descriptor ====\n"
	  << tag.toString() << "--------------\n"
	  << "V Desc Sequence number: " << VDS_number << "\n"
	  << "PVD number: " << number << "\n"
	  << "Id: `" << id << "`\n"
	  << "Sequence number: " << seq_number << " (max: " << max_seq_number << ")\n"
	  << "Interchange Level: " << interchange_level << " (max: "
	  << max_interchange_level << ")\n"
	  << "Charset List: " << charset_list << " (max: " << max_charset_list << ")\n"
	  << "Volume Set ID: `" << set_id << "`\n"
  //
	  << "Volume Abstract: " << vol_abstract.toString()
	  << "Volume Copyright: " << vol_copyright.toString()
	  << "Application Id: " << app_id.toString()
	//
	  << "Implementation Id: " << impl_id.toString()
	  << "Implementation Use: `" << (char*)impl_use << "`\n"
	  << "Previous sequence: " << previous_sequence << "\n"
	  << "Flags: " << flags << "\n";
  return oss.str();
}
