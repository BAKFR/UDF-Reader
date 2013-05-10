
#pragma once

#include "Tag.hpp"

class AVDP;
class Tag;
class PrimaryVDesc;
class PartitionDescriptor;
class LogicalVolumeDescriptor;


class UDF {
public:

  struct Info {
	std::string			volume_id;
	Timestamp			record_time;
	//	std::string			version;
	uint32_t			block_size;
	uint32_t			nb_block;
	//	long long int		free_size;
  };

private:

  int			fd;
  AVDP			*avdp;
  PrimaryVDesc	*pvd;
  PartitionDescriptor *pd;
  LogicalVolumeDescriptor *lvd;

  bool			debug;

  Tag	getTagSector(int type);
public:

  UDF(int fd);

  bool isValid();

  template <typename T>
  T *loadDescriptor(Tag::Type type);

  bool loadAVDP();
  Info *loadInfo();

  void listVDS();
  bool loadPVD();
  bool loadPD();
  bool loadLVD();
  
  ~UDF();
};
