#ifndef DOMAINMODEL_XMDLPAR_XMODEL_HPP
#define DOMAINMODEL_XMDLPAR_XMODEL_HPP

#include "domainModel/global.hpp"

#include "Core" //Eigen/Core

//#include "domainModel/xMDLPAR/xConverter.hpp"

#include "domainModel/xArithCodec/xModel.hpp"
#include "domainModel/xMDLPAR/xErrorDistribution.hpp"
//#include "domainModel/xArithCodec/xRange.hpp"
//#include "domainModel/xMDLPAR/xSymbol.hpp"
//#include "domainModel/xArithCodec/xRangePosition.hpp"

#include <cmath>
#include <vector>

namespace domainModel
{
    namespace xMDLPAR
    {
        class xErrorModel : public domainModel::xArithCodec::xModel
        {
            private:

                typedef int discreteNumberOfIncidentalType;
                static const discreteNumberOfIncidentalType magicNumberMinByteIndex = 0;
                static const discreteNumberOfIncidentalType magicNumberMaxByteIndex = 255;
                static const discreteNumberOfIncidentalType magicNumberNumStatesOfAByte = 256;
		static const discreteNumberOfIncidentalType magicNumberMaxPredictionError = G_MAGIC_NUMBER_MAX_PREDICTION_ERROR; //actual - prediction = error
		static const discreteNumberOfIncidentalType magicNumberMinPredictionError = G_MAGIC_NUMBER_MIN_PREDICTION_ERROR; //actual - prediction = error
		static const discreteNumberOfIncidentalType magicNumberSizeOfErrorRange = magicNumberMaxPredictionError - magicNumberMinPredictionError + 1;
        typedef Eigen::Array<int, magicNumberSizeOfErrorRange, 1> byteInspiredColumnVector;
        typedef Eigen::Array<double,magicNumberSizeOfErrorRange,1> byteInspiredDoubleColumnVector;

		static const int highestCumulativeCount; //2^14 = 16384

                typedef Eigen::Array<int, magicNumberSizeOfErrorRange+1, 1> rangeVector; //257=number of byte states + 1, 1=number of columns
                rangeVector theRange;
                int theScale;


            public:
                xErrorModel();
                xErrorModel(domainModel::xMDLPAR::xErrorDistribution theDistribution);
                domainModel::xArithCodec::xRange GetRange(int theSymbolValue);//domainModel::xMDLPAR::xSymbol theSymbol);
                int GetSymbolValue(int theRangePositionValue);
                short int getScale();
        };
    }
}

#endif
