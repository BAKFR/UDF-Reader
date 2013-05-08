
#pragma once

class AVDP;
class Tag;
class PrimaryVDesc;

class UDF {
private:

  int			fd;
  AVDP			*avdp;
  PrimaryVDesc	*pvd;
  bool			debug;

  Tag	getTagSector(int type);
public:

  UDF(int fd);

  bool isValid();

  bool loadAVDP();
  bool loadInfo();

  void listVDS();

  ~UDF();
};
