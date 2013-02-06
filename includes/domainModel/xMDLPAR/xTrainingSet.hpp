#ifndef DOMAINMODEL_XMDLPAR_XTRAININGSET_HPP
#define DOMAINMODEL_XMDLPAR_XTRAININGSET_HPP

//#include "domainModel/xMDLPAR/xConverter.hpp"

#include "Core" //Eigen/Core

#include "domainModel/global.hpp"

namespace domainModel
{
    namespace xMDLPAR
    {
        class xTrainingSet
        {
            friend class xConverter;
            public:
            xTrainingSet();
            fileIndexType theSize;
            matrixType_ptr supports;
            vectorType_ptr values;
            matrixType_ptr rawSupportIndices;
            bool overdetermined;

        };
    }
}

#endif
