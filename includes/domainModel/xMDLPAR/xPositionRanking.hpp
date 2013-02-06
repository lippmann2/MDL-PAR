#ifndef DOMAINMODEL_XMDLPAR_XPOSITIONRANKING_HPP
#define DOMAINMODEL_XMDLPAR_XPOSITIONRANKING_HPP

#include "Core" //Eigen/Core

#include "domainModel/global.hpp"

#include "boost/smart_ptr/shared_ptr.hpp"

namespace domainModel
{
    namespace xMDLPAR
    {
        class xPositionRanking
        {
            typedef boost::shared_ptr<
                Eigen::Array<fileIndexType,Eigen::Dynamic,1> >
                    positionRankingArrayType;
                //Eigen::Array<fileIndexType,Eigen::Dynamic,1,0,G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES> >
                //    positionRankingArrayType;

            friend class xConverter;
            public:

            xPositionRanking();
            fileIndexType numPositions();

            positionRankingArrayType getPositions();

            //private: //should be private!
            positionRankingArrayType theIndices_ptr;

        };
    }
}

#endif
