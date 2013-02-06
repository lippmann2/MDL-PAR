#ifndef DOMAINMODEL_XMDLPAR_XCONTEXTREPOSITORY_HPP
#define DOMAINMODEL_XMDLPAR_XCONTEXTREPOSITORY_HPP

#include "domainModel/global.hpp"
#include "redBlackTree/red_black_tree.h"
#include "domainModel/xMDLPAR/xContextList.hpp"
//#include "domainModel/xMDLPAR/xConverter.hpp"

inline bool ccpairdescend(const std::pair<double,domainModel::xMDLPAR::xContext>& lhs,
                   const std::pair<double,domainModel::xMDLPAR::xContext>& rhs);

namespace domainModel
{
    namespace xMDLPAR
    {
        class xContextRepository
        {
            public:
            xContextRepository();
            ~xContextRepository();
            xContextList addContextAndGetSimilarContexts(xContext theContext);

            double toOneDee(xContext theContext);

            ////
            //int KeyCompare(const void* a, const void* b);
            //void KeyDestroy(void* a);
            //void InfoDestroy(void* a);
            //void KeyPrint(const void* a);
            //void InfoPrint(void* a);
            ////

            private:
            bool theContextsAreSimilarEnough(const domainModel::xMDLPAR::xContext& a,
                                             const domainModel::xMDLPAR::xContext& b,
                                             double& theDistance);
            double* addContext(xContext theContext); //don't call by itself->memory leak
            rb_red_blk_tree* tree;
        };
    }
}

extern "C" {
    int KeyCompare(const void* a, const void* b);
    void KeyDestroy(void* a);
    void InfoDestroy(void* a);
    void KeyPrint(const void* a);
    void InfoPrint(void* a);
}



#endif
