#ifndef DOMAINMODEL_XARITHCODEC_XSYMBOLMODEL_HPP
#define DOMAINMODEL_XARITHCODEC_XSYMBOLMODEL_HPP

#include "domainModel/global.hpp"

#include "Core" //Eigen/Core

#include <vector>
#include <cmath>

#include "domainModel/xArithCodec/xModel.hpp"
#include "domainModel/xMDLPAR/xSymbolList.hpp"
#include "domainModel/xMDLPAR/xSymbol.hpp"
//#include "domainModel/xArithCodec/xRange.hpp"

namespace domainModel
{
    namespace xArithCodec
    {
        class xSymbolModel : public domainModel::xArithCodec::xModel
        {
            private:
                static const int magicNumberMinByteIndex = 0;
                static const int magicNumberMaxByteIndex = 255;
                static const int magicNumberNumStatesOfAByte = 256;
                typedef Eigen::Array<int, magicNumberNumStatesOfAByte, 1> byteInspiredColumnVector;
                typedef Eigen::Array<double,magicNumberNumStatesOfAByte,1> byteInspiredDoubleColumnVector;
                byteInspiredColumnVector rawSymbolCounts;
                static const int cumulativeCountLimit; //2^14 = 16384


                //holds the scaled range, the actual probability model
                typedef Eigen::Array<int, magicNumberNumStatesOfAByte+1, 1> rangeVector;
                rangeVector theRange;
                int theScale;
                bool upToDate;
                void rescaleModel();

            public:
                //xModel interface:
                domainModel::xArithCodec::xRange GetRange(int theSymbolValue);
                int GetSymbolValue(int theRangePositionValue);
                short int getScale();
                int getSymbolCount(int theSymbolValue);
                void setSymbolCount(int theSymbolValue, fileIndexType theSymbolCount);
                void rescaleAfterReloading();
                xSymbolModel();
                void scanSymbolsForInitialScaling(domainModel::xMDLPAR::xSymbolList theSymbolList);
                void addSymbol(domainModel::xMDLPAR::xSymbol theSymbol);
                void addSymbol(int theSymbolValue);

        };
    }
}

#endif
