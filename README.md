UDF Reader
==========


UDF Reader is a very basic command-line explorer for UDF filesystem.

It was a proposed subject for courses of Project Training,
from Beijing Jiaotong University (Beijing, China).

___

At current version, It only display some informations about the UDF file:

 - check if file is really an UDF file
 - access to AVDP sector and dump it
 - access to Primary Volume Descriptor and dump it

An UDF file msut be passed in argument:

```bash
$> make
$> ./UDF_reader my_UDF_file.iso
Is it a valid UDF file ? true
Loading AVDP ....
TAG Type 2
version: 2
checksum: 116 (true)
serial: 0
CRC: 26136 (length = 496)
location: 256 (true)
--------------
main Volume Descriptor Sequence: extent_ad(length: 32768, location: 257)
reserve Volume Descriptor Sequence: extent_ad(length: 32768, location: 275)

# ... more info displayed ...
```
