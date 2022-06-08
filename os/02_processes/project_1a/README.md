# Example usage

$ echo "abbcccddddeeeeeffffff" > compressible_data
$ ./wcat compressible_data
abbcccddddeeeeeffffff

$ ./wzip compressible_data > compressed_data
$ hexdump -C compressed_data
00000000  01 00 00 00 61 02 00 00  00 62 03 00 00 00 63 04  |....a....b....c.|
00000010  00 00 00 64 05 00 00 00  65 06 00 00 00 66        |...d....e....f|
0000001e

$ ./wunzip compressed_data > original_data
$ ./wcat original_data
abbcccddddeeeeeffffff

