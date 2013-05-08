
#include <sstream>
#include <unistd.h>
#include "AVDP.hpp"
#include "Tag.hpp"

AVDP::AVDP()
  : tag(256)
{}


AVDP	*AVDP::getAVDPFromFd(int fd) {
  if (lseek(fd, 2048 * 256, SEEK_SET) != 2048 * 256)
	return NULL;

  uint8_t buffer[32];

  if (read(fd, buffer, 32) != 32)
	return NULL;

  AVDP *avdp = new AVDP();
  avdp->tag.setData(buffer);
  avdp->main_VDecSeq.setData(buffer + 16);
  avdp->reserve_VDecSeq.setData(buffer + 24);
  return avdp;
}

std::string		AVDP::toString() const {
  return std::string("==== AVDP ====\n")
	+ tag.toString() + "--------------\n"
	+ "main Volume Descriptor Sequence: " + main_VDecSeq.toString()
	+ "reserve Volume Descriptor Sequence: " + reserve_VDecSeq.toString();
}

bool AVDP::isValid() const {
  return tag.isValid() && tag.type == Tag::AVDP;
}

const extend_ad  &AVDP::getMainVDS() const {
  return main_VDecSeq;
}
