
#include "Descriptor.hpp"
#include "DString.hpp"

class FileSetDesc : public Descriptor
{
protected:
  Timestamp		record_time;
  uint16_t		inter_lvl;
  uint16_t		max_inter_lvl;
  uint32_t		charset_list;
  uint32_t		max_charset_list;
  uint32_t		fileset_nbr;
  uint32_t		max_fileset_nbr;
  charspec		lv_id_charset;
  DString		lv_id;
  charspec		fs_charset;
  DString		fs_id;
  DString		copyright_id;
  DString		abstract_id;
  //extend_ad		root_dir_ICB;
  regid			domain_id;
  //extend_ad		next_extent;
  //extend_ad		stream_dir_ICB;
public:
  FileSetDesc();
  void	setData(uint8_t *buffer);
  std::string  toString() const;

};
