#ifndef DOMAINMODEL_XMDLPAR_XPREDICTIONCOMPONENTS_HPP
#define DOMAINMODEL_XMDLPAR_XPREDICTIONCOMPONENTS_HPP

#include "domainModel/global.hpp"

#include "domainModel/xMDLPAR/xErrorDistribution.hpp"
#include "domainModel/xMDLPAR/xSupportMask.hpp"
#include "domainModel/xMDLPAR/xFilterCoefficients.hpp"

namespace domainModel
{
    namespace xMDLPAR
    {
        class xPredictionComponents
        {
            public:
            //xPredictionComponents(
            //                      domainModel::xMDLPAR::xErrorDistribution errorDistribution,
            //                      domainModel::xMDLPAR::xSupportMask supportMask,
            //                      domainModel::xMDLPAR::xFilterCoefficients filterCoefficients);
            xPredictionComponents();
            bool meaningfulPrediction;
            domainModel::xMDLPAR::xErrorDistribution theErrorDistribution;
            domainModel::xMDLPAR::xSupportMask theSupportMask;
            domainModel::xMDLPAR::xFilterCoefficients theFilterCoefficients;
        };
    }
}

#endif
