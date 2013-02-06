#ifndef DOMAINMODEL_XMDLPAR_XPREDICTOR_HPP
#define DOMAINMODEL_XMDLPAR_XPREDICTOR_HPP

#include <limits>
#include <cmath>

#include "Core" //Eigen/Core

#include "domainModel/global.hpp"
#include "domainModel/xMDLPAR/xConverter.hpp"
#include "domainModel/xMDLPAR/xPredictionComponents.hpp"
#include "domainModel/xMDLPAR/xSupportMask.hpp"
#include "domainModel/xMDLPAR/xFilterCoefficients.hpp"
//#include "domainModel/xMDLPAR/xErrorDistribution.hpp"
//#include "domainModel/xMDLPAR/xConverter.hpp"
#include "domainModel/xMDLPAR/xContextRepository.hpp"

namespace domainModel
{
    namespace xMDLPAR
    {
        class xPredictor
        {
            public:
            static domainModel::xMDLPAR::xPredictionComponents
                getPredictionComponents(domainModel::xMDLPAR::xSymbolList theCausalSymbols,
                                        domainModel::xMDLPAR::xContext theSymbolContext,
                                        domainModel::xMDLPAR::xContextRepository* theContextRepository_ptr);

            static int getError(domainModel::xMDLPAR::xSupportMask theSupportMask,
                                domainModel::xMDLPAR::xFilterCoefficients theFilterCoefficients,
                                domainModel::xMDLPAR::xContext theContext,
                                domainModel::xMDLPAR::xSymbol theSymbol);

            static int applyFilter(domainModel::xMDLPAR::xFilterCoefficients theFilterCoefficients,
                                   domainModel::xMDLPAR::xContext theHeadContext,
                                   domainModel::xMDLPAR::xSupportMask theSupportMask);

            static domainModel::xMDLPAR::xContextList
                getSimilarContexts(
                    domainModel::xMDLPAR::xSymbolList theSymbolList,
                    domainModel::xMDLPAR::xContext theComparisonContext);

            static bool
                theContextsAreSimilarEnough(
                    const domainModel::xMDLPAR::xContext& a,
                    const domainModel::xMDLPAR::xContext& b);

            static bool
                theSupportsAreSimilarEnough(
                rowVectorType_ptr a,
                rowVectorType_ptr b);

            static double getStd(
                domainModel::xMDLPAR::xTrainingSet theTrainingSet,
                domainModel::xMDLPAR::xFilterCoefficients theFilterCoefficients);

            static double getH(
                domainModel::xMDLPAR::xErrorDistribution theErrorDistribution);

        };
    }
}

#endif
