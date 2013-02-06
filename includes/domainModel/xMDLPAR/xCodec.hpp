#ifndef DOMAINMODEL_XMDLPAR_XCODEC_HPP
#define DOMAINMODEL_XMDLPAR_XCODEC_HPP

#include "domainModel/global.hpp"

#include <string>
#include <fstream>
#include <iostream>
#include <time.h>

#include "boost/smart_ptr/shared_ptr.hpp"

#include "domainModel/xMDLPAR/xConverter.hpp"
//#include "domainModel/xMDLPAR/xSymbolList.hpp"
//#include "domainModel/xMDLPAR/xCodecBuffer.hpp"
#include "domainModel/xArithCodec/xSymbolModel.hpp"
#include "domainModel/xArithCodec/xArithEncoder.hpp"
#include "domainModel/xArithCodec/xArithDecoder.hpp"
//#include "domainModel/xMDLPAR/xErrorDistribution.hpp"
#include "domainModel/xArithCodec/xRange.hpp"
#include "domainModel/xMDLPAR/xErrorModel.hpp"
#include "domainModel/xMDLPAR/xPredictionComponents.hpp"
#include "domainModel/xMDLPAR/xPredictor.hpp"
//#include "domainModel/xMDLPAR/xFilterCoefficients.hpp"
#include "domainModel/xMDLPAR/xContextRepository.hpp"

namespace domainModel
{
    namespace xMDLPAR
    {
        class xCodec
        {

            public:
                //xCodec(boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer> theCodecBuffer_ptr);
                xCodec();
                ~xCodec();
                void compressTo(const std::string& theOriginalFileNameAndPath,
                                const std::string& theCompressionFileNameAndPath);
                void decompressTo(const std::string& theCompressedFileNameAndPath,
                                  const std::string& theDecompressedFileNameAndPath);
                bool theFilesAreEquivalent(const std::string& theOriginalFileNameAndPath,
                             const std::string& theDecompressedFileNameAndPath);

                #ifdef MYDEBUG
                    std::ofstream clog, dlog;
                #endif

            //private:
                //boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer> codecBuffer_ptr;
        };
    }
}

#endif
