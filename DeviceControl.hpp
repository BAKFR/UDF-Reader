#pragma once

#include <stdint.h>

class DeviceControl
{
protected:
  int fd;
public:
  DeviceControl();
  bool canReadDVD();
  int getDVDFileDescriptor();
  bool getSector(unsigned int i, uint8_t *buffer);
};
