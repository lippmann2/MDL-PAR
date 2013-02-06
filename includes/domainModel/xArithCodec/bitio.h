//slightly adapted from the data compression book 2nd ed.

#ifndef _BITIO_H
#define _BITIO_H

//#include "domainModel/global.hpp"

#include <stdio.h>

extern unsigned long bytesWritten;

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bit_file {
	FILE *file;
	unsigned char mask;
	int rack;
	int pacifier_counter;
} BIT_FILE;

BIT_FILE* OpenInputBitFile(const char *name );
BIT_FILE* OpenOutputBitFile(const char *name );
void OutputBit( BIT_FILE *bit_file, int bit );
void OutputBits( BIT_FILE *bit_file, unsigned long code, int count );

void AlignToBoundary( BIT_FILE *bit_file);

int InputBit( BIT_FILE *bit_file );
unsigned long InputBits( BIT_FILE *bit_file, int bit_count );
void CloseInputBitFile( BIT_FILE *bit_file );
void CloseOutputBitFile( BIT_FILE *bit_file );
void FilePrintBinary( FILE *file, unsigned int code, int bits);

#ifdef __cplusplus
}
#endif

#endif /* _BITIO_H */
