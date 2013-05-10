
#pragma once

class AVDP;
class Tag;
class PrimaryVDesc;
class PartitionDescriptor;

class UDF {
private:

  int			fd;
  AVDP			*avdp;
  PrimaryVDesc	*pvd;
  PartitionDescriptor *pd;
  bool			debug;

  Tag	getTagSector(int type);
public:

  UDF(int fd);

  bool isValid();

  bool loadAVDP();
  bool loadInfo();

  void listVDS();
  bool loadPartitionDescriptor();

  ~UDF();
};
