
#include <sstream>
#include <unistd.h>
#include <cstring>
#include "Tag.hpp"


Tag::Tag(uint32_t location)
  : real_location(location)
{

}

void	Tag::setData(uint8_t *buffer) {
  type = ((uint16_t*) buffer)[0];
  version = ((uint16_t*) buffer)[1];
  checksum = buffer[4];
  serial = ((uint16_t*) (buffer + 6))[0];
  CRC = ((uint16_t*) (buffer + 8))[0];
  CRC_length = ((uint16_t*) (buffer + 10))[0];
  location = ((uint16_t*) (buffer + 12))[0];
};

bool	Tag::isChecksumOK() const {
  uint8_t sum = type % 256 + type / 256
	+ version % 256 + version / 256
	+ serial % 256 + serial / 256
	+ CRC % 256 + CRC / 256
	+ CRC_length % 256 + CRC_length / 256
	+ location % 256 + (location >> 8) % 256
	+ (location >> 16) % 256
	+ (location >> 24) % 256;

  return checksum == sum;
}

bool	Tag::isLocationOK() const {
  return location == real_location;
}

bool	Tag::isValid() const {
  return isChecksumOK() && isLocationOK();
}

std::string		Tag::toString() const {
  std::ostringstream oss;

  oss.flags(std::ios_base::boolalpha);
  oss << "Tag" << "\n"
	  << "Type: " << type << "\n"
	  << "version: " << (int)version << "\n"
	  << "checksum: " << (int) checksum << " (" << isChecksumOK() << ")\n"
	  << "serial: " << serial << "\n"
	  << "CRC: " << CRC << " (length = " << CRC_length << ")\n"
	  << "location: " << location << " (" << (location == real_location) << ")\n";

  return oss.str();

}



void		extend_ad::setData(uint8_t *buffer) {
  length = ((int32_t*) buffer)[0];
  location = ((int32_t*) buffer)[1];
}

std::string		extend_ad::toString() const {
  std::ostringstream oss;

  oss << "extent_ad(length: " << length
	  << ", location: " << location << ")\n";
  return oss.str();

}

void		regid::setData(uint8_t *buffer) {
  flags = buffer[0];
  isDirty = flags & 1;
  isProtected = flags & 2;
  memcpy(id, buffer + 1, 23);
  id[23] = '\0';
  memcpy(suffix, buffer + 24, 8);
  suffix[8] = '\0';
}

std::string		regid::toString() const {
  std::ostringstream oss;

  oss.flags(std::ios_base::boolalpha);
  oss << "regid -> `" << id << "`\n"
	  << "\t Flags: " << (int) flags << " ( "
	  << "Dirty? " << isDirty << ", Protected? " << isProtected << ")\n";
  return oss.str();

}
