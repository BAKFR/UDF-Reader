
#include "FileSetDesc.hpp"
#include <sstream>

FileSetDesc::FileSetDesc()
  : Descriptor("File Set Descriptor", 480)
{
}

void			FileSetDesc::setData(uint8_t *buffer) {
  record_time.setData(buffer);
  buffer += 12;
  inter_lvl = ((uint16_t*)buffer)[0];
  max_inter_lvl = ((uint16_t*)buffer)[1];
  buffer += 4;
  charset_list = ((uint32_t*)buffer)[0];
  max_charset_list = ((uint32_t*)buffer)[1];
  fileset_nbr = ((uint32_t*)buffer)[2];
  max_fileset_nbr = ((uint32_t*)buffer)[3];
  buffer += 16;
  lv_id_charset.setData(buffer);
  buffer += 64;
  lv_id.setData(buffer, 128, &lv_id_charset);
  buffer += 128;
  fs_charset.setData(buffer);
  buffer += 64;
  fs_id.setData(buffer, 32, &fs_charset);
  buffer += 32;
  copyright_id.setData(buffer, 32, &fs_charset);
  buffer += 32;
  abstract_id.setData(buffer, 32, &fs_charset);
  buffer += 32;
  
  buffer += 16;
  domain_id.setData(buffer);
  buffer += 32;
  //
  //
}

std::string		FileSetDesc::toString() const {
  std::ostringstream oss;
  
  oss << Descriptor::toString()
	  << "Recording Date and Time: " << record_time.toString() << "\n"
	  << "Interchange Level: " << inter_lvl << "\n"
	  << "Max Interchange Level: " << max_inter_lvl << "\n"
	  << "Charset List: " << charset_list << "\n"
	  << "Max Charset List: " << max_charset_list << "\n"
	  << "File Set Number: " << fileset_nbr << "\n"
	  << "Max File Set Number: " << max_fileset_nbr << "\n"
	  << "LV ID charset: " << lv_id_charset.toString() << "\n"
	  << "LV ID: " << lv_id.toString() << "\n"
	  << "FileSet charset: " << fs_charset.toString() << "\n"
	  << "FileSet ID: " << fs_id.toString() << "\n"
	  << "Copyright ID: " << copyright_id.toString()<< "\n"
	  << "Abstract ID: " << abstract_id.toString() << "\n"
	//
	  << "Domain ID: " << domain_id.toString();
	//
  return oss.str();
}
