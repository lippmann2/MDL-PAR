//Lightly adapted from The Data Compression Book 2nd Ed.

#ifndef DOMAINMODEL_XARITHCODEC_XARITHDECODER_HPP
#define DOMAINMODEL_XARITHCODEC_XARITHDECODER_HPP

#include "domainModel/global.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include "domainModel/xArithCodec/bitio.h"
#include "domainModel/xArithCodec/errhand.h"

#include "domainModel/xArithCodec/xModel.hpp"
//#include "domainModel/xMDLPAR/xErrorModel.hpp"
#include "domainModel/xArithCodec/xRange.hpp"
#include "domainModel/xArithCodec/xSymbolModel.hpp"

namespace domainModel
{
    namespace xArithCodec
    {
        class xArithDecoder
        {
        public:
            typedef struct {
                unsigned short int low_count;
                unsigned short int high_count;
                unsigned short int scale;
            } SYMBOL;

            xArithDecoder();
            void initialize(
                const char* theFileToBeDecompressedFileNameAndPath);//,
                //char* theOutputFileNameAndPath);
            int decodeSymbol(domainModel::xArithCodec::xModel& theModel);
            void finish();

            domainModel::xArithCodec::xSymbolModel getSavedSymbolModel();
            fileIndexType getOriginalFileSizeInBytes();

        private:
            fileIndexType originalFileSizeInBytes;
            domainModel::xArithCodec::xSymbolModel savedSymbolModel;

            void initialize_arithmetic_decoder(BIT_FILE *stream);
            void remove_symbol_from_stream(BIT_FILE *stream, SYMBOL *s);

            unsigned short int low;
            unsigned short int high;
            unsigned short int code;
            long underflow_bits;

            SYMBOL s;
            BIT_FILE *input;

            #ifdef MYDEBUG
                std::ofstream dlog;
            #endif
            //FILE *output;
        };
    }
}

#endif
