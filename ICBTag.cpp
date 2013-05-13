
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

std::string		ICBTag::toString() const {
  std::ostringstream oss;

  oss.flags(std::ios_base::boolalpha);
  oss << "ICB Tag" << "\n"
	  << "Prior Recorded Number of Direct Entries: " << nb_prior_direct_entries
	  << "\nStrategy: Type = " << strategy_type << "\n"
	  << "\tArgs: " << (int) strategy_args[0] << " " << (int)strategy_args[1] << "\n"
	  << "Max Number of Entries: " << max_nb_entries << "\n"
	  << "File Type: " << file_type << "\n"
	  << "Parent ICB Location: " << parent_ICB.toString() << "\n"
	  << "Flags: " << flags
	  << "\n--------------\n";
  return oss.str();

}
