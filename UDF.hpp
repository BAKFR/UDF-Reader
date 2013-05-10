
#pragma once

class AVDP;
class Tag;
class PrimaryVDesc;
class PartitionDescriptor;
class LogicalVolumeDescriptor;


class UDF {
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

  bool loadAVDP();
  bool loadInfo();

  void listVDS();
  bool loadPartitionDescriptor();
  bool loadLVD();
  
  ~UDF();
};
