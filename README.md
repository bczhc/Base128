Base128
=======

**It is a base64-based variant encoding.**

---

But we can't find 128 printable characters in ASCII, so it converts the binary stream to a binary stream.

Its encoded length is 14.29% smaller than Base64, and echo 7 bytes is encoded into 8 bytes.

The file header occupies 8 bytes and is used to store some information like the length of the original file.

The algorithm of this program is for binary streams. Also, it can be used as a compression algorithm for ASCII texts (only to do a Base128 decoding to the text).
This feature has not yet reached its best, and it needs to be improved continually.

This program's encoding/decoding speed is not very fast, and in fact, it can be more perfect...

The .c files is the C language source code, Base128.exe is the compiled program, run in cmd, using:


>Base128 (-encode | -decode) <src-file-path> [<dest-file-path>]
