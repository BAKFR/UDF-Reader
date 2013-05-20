UDF Reader
==========


UDF Reader is a very basic command-line explorer for UDF filesystem.

It was a proposed subject for courses of Project Training,
from Beijing Jiaotong University (Beijing, China).

___

An UDF file must be passed in argument:

```bash
$> make
$> ./UDF_reader my_UDF_file.iso	# or with a real DVD: ./UDF_reader /dev/sr0
Is it a valid UDF file ? true
$> # type commands here
$>exit
```


When started, it provides a basic prompt where you can execute some commands:

 - `dir`: display informations about current directory and it's content.
 - `cd`: move into UDF subdirectories.
 - `cp`: copy a file from UDF file system.
   **example:** `cp myFileFromDisk.txt ~/file.txt`
 - `exit` for exitting the program.

