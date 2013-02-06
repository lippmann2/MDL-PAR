#ifndef DOMAINMODEL_XMDLPAR_XERRORDISTRIBUTION_HPP
#define DOMAINMODEL_XMDLPAR_XERRORDISTRIBUTION_HPP

#include "domainModel/global.hpp"

namespace domainModel
{
    namespace xMDLPAR
    {
        class xErrorDistribution
        {
            public:
                static const double flatDistributionHeight;
                static const double maxAbsoluteError;

                xErrorDistribution();
                xErrorDistribution(double theStd);
                double Pd(int theSymbolError);
                bool isFlat();

            //private:
                bool flatDistribution;
                double theStandardDeviation;
        };
    }
}

#endif
