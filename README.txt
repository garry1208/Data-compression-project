DATA COMPRESSION PROJECT

ALGORITHM 1: HUFFMAN COMPRESSION TECHNIQUE  (STATUS : PENDING)

IT IS TO BE RUN THROUGH COMMAND LINE ITSELF

USAGE IS : <output command> <INPUT FILE NAME> <DESTINATION FILENAME> -C(-c)(for compression)|-DC(-dc)(for decompression)

the file is compressed in destination file using frequency count and by huffman tree using encoded strings(bits).

decompression work is in progress.

sample input & output files are included in repository to show how both files will look like.

NOTE: WORKS ONLY FOR ASCII FILES.


ALGORITHM 2: RUN LENGTH ENCODING  (STATUS : DONE)

FOR COMRESSING THE ASCII FILE:
usage is :cc -Wall rle_compression.c 
          <a.out> <source> <destination>

FOR DECOMRESSING THE BINARY FILE:
usage is :cc -Wall rle_decompression.c 
          <a.out> <source> <destination>

It counts repitative characters in an ascii string and just writes the character and its count in the encoded string.

When there are no repitative characters the file size is greater than input because of the counts that are stored after each  character.

