#ifndef DOMAINMODEL_XMDLPAR_XFILTERCOEFFICIENTS_HPP
#define DOMAINMODEL_XMDLPAR_XFILTERCOEFFICIENTS_HPP

#include "domainModel/global.hpp"

namespace domainModel
{
    namespace xMDLPAR
    {
        class xFilterCoefficients
        {
            friend class xConverter;
            public:
                vectorType_ptr filterCoefficients;
                double rank;
        };
    }
}

#endif
