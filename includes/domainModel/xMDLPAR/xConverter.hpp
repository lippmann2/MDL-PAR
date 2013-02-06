#ifndef DOMAINMODEL_XMDLPAR_XCONVERTER_HPP
#define DOMAINMODEL_XMDLPAR_XCONVERTER_HPP

#include "domainModel/global.hpp"

//order matters?
#include "domainModel/xMDLPAR/xSymbol.hpp"
#include "domainModel/xMDLPAR/xSymbolList.hpp"
#include "domainModel/xMDLPAR/xContext.hpp"
#include "domainModel/xMDLPAR/xCodecBuffer.hpp"
#include "domainModel/xMDLPAR/xContextList.hpp"
#include "domainModel/xMDLPAR/xPositionRanking.hpp"
#include "domainModel/xMDLPAR/xSupportMask.hpp"
#include "domainModel/xMDLPAR/xTrainingSet.hpp"
#include "domainModel/xMDLPAR/xPredictor.hpp"
#include "domainModel/xMDLPAR/xFilterCoefficients.hpp"
//#include "domainModel/xMDLPAR/xContextRepository.hpp"

//#include "Dense" //Eigen/Dense
#include "Core" //Eigen/Core
#include "SVD" //Eigen/SVD
#include "LU" //Eigen/LU

//class std::vector;

namespace domainModel
{
    namespace xMDLPAR
    {
        class xConverter
        {

            //class xSymbol;
            //class xSymbolList;
            //class xContext;
            //class xCodecBuffer;

            //whoops, these will be eigen3 representations (and a scalar of some sort)
            //typedef int symbolAsValue;
            //typedef Eigen::ArrayXd symbolsAsValues;

            //symbol + codecBuffer --> byteValue
            public:
            static symbolAsValue toValue(const xSymbol& theSymbol); //, const xCodecBuffer& theCodecBuffer);

            //symbol --> symbolList (causal symbols)
            static domainModel::xMDLPAR::xSymbolList toCausalSymbols(const xSymbol& theSymbol);

            //symbol -->key context (adjacent context not inclusive context)
            static domainModel::xMDLPAR::xContext toCausalAdjacentContext(const xSymbol& theSymbol);

            static symbolsAsValues toValues(const domainModel::xMDLPAR::xContext& theContext);

            static int toAdjacentSymbolValue(domainModel::xMDLPAR::xContext theContext);

            static Eigen::Array<double,Eigen::Dynamic,1>
                toAdjacentSymbolValues(domainModel::xMDLPAR::xContextList theContextList);

            static Eigen::Array<double,Eigen::Dynamic,1>
                toSymbolValuesAtIndex(fileIndexType theIndex,
                                      domainModel::xMDLPAR::xContextList theContextList);

            //get indices of positive sorted correlations
            static domainModel::xMDLPAR::xPositionRanking
                toPositionRanking(domainModel::xMDLPAR::xContextList theContextList);

            //context + codecBuffer --> byteValues
            //static symbolsAsValues toValues(const xContext& theContext, const xCodecBuffer& theCodecBuffer);

            //symbolList + codecBuffer --> byteValues
            //static symbolsAsValues toValues(const xSymbolList& theSymbolList, const xCodecBuffer& theCodecBuffer);

            //codecBuffer --> symbolList
            //static domainModel::xMDLPAR::xSymbolList toSymbolList(
            //     boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer> theCodecBuffer_ptr);
            static domainModel::xMDLPAR::xSymbolList toSymbolList(domainModel::xMDLPAR::xCodecBuffer* theCodecBuffer_ptr);

            //context --> symbol
            //static xSymbol toHeadSymbol(const xContext& theContext); //last symbol included by context
            //static xSymbol toKeySymbol(const xContext& theContext); //symbol adjacent to causal context

            //symbolList --> context
            static xContext toHeadContext(const xSymbolList& theSymbolList);

            static xTrainingSet toTrainingSet(domainModel::xMDLPAR::xContextList theContextList,
                                              domainModel::xMDLPAR::xSupportMask theSupportMask,
                                              domainModel::xMDLPAR::xContext thePredictionContext);

            static rowVectorType_ptr toSupport(domainModel::xMDLPAR::xSupportMask theSupportMask,
                                            domainModel::xMDLPAR::xContext theContext);

            static rowVectorType_ptr toRawSupportIndices(domainModel::xMDLPAR::xSupportMask theSupportMask,
                                                         domainModel::xMDLPAR::xContext theContext);

            static xFilterCoefficients toFilterCoefficients(xTrainingSet theTrainingSet, fileIndexType k);

            //static double toOneDee(xContext theContext);

            //context --> symbolList
            //static xSymbolList toSymbolList(const xContext& theContext);

        };
    }
}

#endif
