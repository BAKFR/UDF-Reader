
#pragma once

#include "Tag.hpp"

class AVDP;
class Tag;
class PrimaryVDesc;
class PartitionDescriptor;
class LogicalVolumeDescriptor;
class UnallocSpaceDesc;

class UDF {
public:

  struct Info {
	std::string			volume_id;
	Timestamp			record_time;
	//	std::string			version;
	uint32_t			block_size;
	uint32_t			nb_block;
	long double			free_size;
  };

private:

  int			fd;
  AVDP			*avdp;
  PrimaryVDesc	*pvd;
  PartitionDescriptor	*pd;
  LogicalVolumeDescriptor *lvd;
  UnallocSpaceDesc		*usd;

  bool			debug;

  Tag	getTagSector(int type);
public:

  UDF(int fd);

  bool isValid();

  template <typename T>
  T *loadDescriptor(Tag::Type type);

  bool loadAVDP();
  Info *loadInfo();

  bool loadPVD();
  bool loadPD();
  bool loadLVD();
  bool loadUSD();

  void	listPartition();
  void	listMVDS();
  void	listVDS(const extend_ad &ext);
  
  ~UDF();
};
