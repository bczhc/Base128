Base128
=======

**It is a Base64 - based variant encoding.**

But we can't find 128 printable print characters in ASCII, so it converts the binary stream to binary stream.

And its encoded length is 14.29% smaller than Base64, and every 7 bytes is encoded into 8 bytes.

But the file header occupies 8 bytes and is used to store some information to ensure that the source file is identical to the source file after it has been encoded and decoded.

The algorithm of this program is for binary streams. For characters in pure ASCII, it can be used as a compression algorithm (only ASCII text needs to be decoded), but for all streams, including all other files, And characters other than ASCII, it can't be compressed, it can only be encoded.
This feature has not yet reached its best, and will continue to update the ability to compress files in the ASCII stream range in ASCII.

This program encoding/decoding speed is not very fast, in fact, it can be more perfect...

The .c file is the c language source code, Base128.exe is the compiled program, run in cmd, using:

>Base128 \[-encode | -decode\] \[\[filePath\]\] \[\[DestFilePath\]\] |
Base128 \[-encode | -decode\] \[\[filePath\]\]
