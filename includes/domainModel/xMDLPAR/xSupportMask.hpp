#ifndef DOMAINMODEL_XMDLPAR_XSUPPORTMASK_HPP
#define DOMAINMODEL_XMDLPAR_XSUPPORTMASK_HPP

#include "Core" //Eigen/Core

#include "domainModel/global.hpp"

#include "domainModel/xMDLPAR/xPositionRanking.hpp"
#include "domainModel/xMDLPAR/xSupportMask.hpp"

namespace domainModel
{
    namespace xMDLPAR
    {
        class xSupportMask
        {
            friend class xConverter;
            public:
            typedef boost::shared_ptr<
                Eigen::Array<fileIndexType,Eigen::Dynamic,1> >
                    supportMaskArray_ptr;
                //Eigen::Array<fileIndexType,Eigen::Dynamic,1,0,G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES> >
                //    supportMaskArray_ptr;

            xSupportMask();
            xSupportMask(domainModel::xMDLPAR::xPositionRanking thePositionRanking,
                         fileIndexType theK);
            fileIndexType getSize();

            supportMaskArray_ptr getSupportMask();

            private:

            fileIndexType k;

            //supportMaskArray_ptr theIndices_ptr;
            supportMaskArray_ptr theShortenedPositionRanking_ptr;
        };
    }
}

#endif
