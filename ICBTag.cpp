
#include "ICBTag.hpp"
#include <sstream>
#include <cstring>

void	ICBTag::setData(uint8_t *buffer)
{
  nb_prior_direct_entries = ((uint32_t*) buffer)[0];
  strategy_type = ((uint16_t*) (buffer + 4))[0];
  memcpy(strategy_args, buffer + 6, 2);
  max_nb_entries = ((uint16_t*) (buffer + 8))[0];
  file_type = buffer[11];
  parent_ICB.setData(buffer + 12);
  flags = ((uint16_t*) (buffer + 18))[0];
}

std::string		ICBTag::getStrFileType() const {
  switch (file_type) {
  case 1:
	return "Unallocated Space Entry";
  case 2:
	return "Partition Integrity Table";
  case 3:
	return "Indirect Entry";
  case 4:
	return "Directory";
  case 5:
	return "Byte Sequence";
  case 6:
	return "Special Block Device";
  case 7:
	return "Special Character Device";
  case 8:
	return "FIFO";
  case 9:
	return "C_ISSOCK";
  case 11:
	return "Terminal Entry";
  case 12:
	return "Symbolic Link";
  case 13:
	return "Stream Directory";
  default:
	return "Unknow type";
  }
}

std::string ICBTag::displayFlags() const {
  std::ostringstream oss;

  char type_ad = flags & 0x04;
  oss << "Type AD: ";
  switch (type_ad) {
  case 0:
	oss << "short_ad";
	break;
  case 1:
	oss << "long_ad";
	break;
  case 2:
	oss << "ext_ad";
	break;
  case 3:
	oss << "inline content";
	break;
  default:
	oss << "unknown";
  }
  return oss.str();
}

int		ICBTag::getTypeAd() const {
  return flags & 0x04;
}

std::string		ICBTag::toString() const {
  std::ostringstream oss;

  oss.flags(std::ios_base::boolalpha);
  oss << "ICB Tag" << "\n"
	  << "Prior Recorded Number of Direct Entries: " << nb_prior_direct_entries
	  << "\nStrategy: Type = " << strategy_type << "\n"
	  << "\tArgs: " << (int) strategy_args[0] << " " << (int)strategy_args[1] << "\n"
	  << "Max Number of Entries: " << max_nb_entries << "\n"
	  << "File Type: " << (int)file_type << " -- " << getStrFileType() << "\n"
	  << "Parent ICB Location: " << parent_ICB.toString() << "\n"
	  << "Flags: " << flags << "\n"
	  << "\t" << displayFlags()
	  << "\n--------------\n";
  return oss.str();

}
