#include "DeviceControl.hpp"
#include <unistd.h>
#include <fcntl.h>

DeviceControl::DeviceControl() {
  fd = -1;
}

bool DeviceControl::canReadDVD() {
  fd = open("/dev/sr0", O_RDONLY);
  if (fd < 2) {
    return false;
  } else {
    return true;
  }
}

int DeviceControl::getDVDFileDescriptor() {
  if (fd == -1) {
    if (canReadDVD()) {
      return fd;
    } else {
      return -1;
    }
  } else {
    return fd;
  }
}

bool DeviceControl::getSector(unsigned int i, uint8_t *buffer) {
  int offset = i * 2048;
  if (lseek(fd, offset, SEEK_SET) < 0) {
    return false;
  }
  if (read(fd, buffer, 2048) < 0) {
    return false;
  }
  return true;
}
