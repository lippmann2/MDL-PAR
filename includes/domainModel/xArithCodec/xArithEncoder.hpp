//Lightly adapted from The Data Compression Book 2nd Ed.

#ifndef DOMAINMODEL_XARITHCODEC_XARITHENCODER_HPP
#define DOMAINMODEL_XARITHCODEC_XARITHENCODER_HPP

#include <fstream>

#include "domainModel/global.hpp"

//#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "domainModel/xArithCodec/bitio.h"
#include "domainModel/xArithCodec/errhand.h"
#include "domainModel/xArithCodec/xRange.hpp"
#include "domainModel/xArithCodec/xSymbolModel.hpp"

//#define END_OF_STREAM 256

namespace domainModel
{
	namespace xArithCodec
	{
		class xArithEncoder
		{
		public:

            typedef struct {
                unsigned short int low_count;
                unsigned short int high_count;
                unsigned short int scale;
            } SYMBOL;

            xArithEncoder();
			void initialize(const char* theOutputFileNameAndPath,
                   fileIndexType numBytesCurrentlyInBuffer);
			void encodeSymbol(domainModel::xArithCodec::xRange theRange);
			void finish(domainModel::xArithCodec::xSymbolModel theSymbolModel);

		private:

            fileIndexType fileSizeToBeEncoded;

            //void convert_int_to_symbol(int theSymbolValue, SYMBOL *s);
            void encode_symbol( BIT_FILE *stream, SYMBOL *s );
            void flush_arithmetic_encoder(BIT_FILE *stream);

            unsigned short int low;
            unsigned short int high;
            long underflow_bits;

            const char* outputFileNameAndPath;

			SYMBOL s;
			BIT_FILE *output;
		};
	}
}

#endif
