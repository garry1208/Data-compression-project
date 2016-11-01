                                          TITLE :  DATA COMPRESSION PROJECT(HUFFMAN, LZW, RLE)

NAME : ROHIT SANJAY KHOLE

MIS ID : 111503034

DESCRIPTION:

ALGORITHM 1: HUFFMAN COMPRESSION TECHNIQUE

IT IS TO BE RUN THROUGH COMMAND LINE ITSELF

USAGE IS : <output command> <INPUT FILE NAME> <DESTINATION FILENAME> <-c(for compression)|-dc(for decompression)> <huffman | rle | lzw >  

the file is compressed in destination file using frequency count and by huffman tree using encoded strings(bits).

NOTE: WORKS ONLY FOR ASCII FILES.


ALGORITHM 2: RUN LENGTH ENCODING 

It counts repitative characters in an ascii string and just writes the character and its count in the encoded string.

When there are no repitative characters the file size is greater than input because of the counts that are stored after each  character.

ALGORITHM 3 : LEMPEL ZIV WELCH (LZW) COMPRESSION

It maintains a dictionary when compressing such that when new sequence stored is encountered it writes the new code to the dictionary thus an extended form of ascii table. it then writes these corresponding codes to the compressed file.

NOTE : Due to limitations of dictionary size ( 4096 ) it can handle files upto specific limit.
