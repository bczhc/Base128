Base128
=======

It is a Base64 - based variant encoding.

But we can't find 128 printable print characters in ASCII, so it converts the binary stream to binary stream.

And its encoded length is 14.29% smaller than Base64, and every 7 bytes is encoded into 8 bytes.

But the file header occupies 8 bytes and is used to store some information to ensure that the md5 of the source file is the same as the md5 of the file it encodes and then decodes.

This program encoding/decoding speed is not very fast, in fact, it can be more perfect...

The .c file is the c language source code, Base128.exe is the compiled program, run in cmd, using:

Base128 [-encode | -decode] [[filePath]] [[DestFilePath]] |
Base128 [-encode | -decode] [[filePath]]
