#include "domainModel/xMDLPAR/xPositionRanking.hpp"

domainModel::xMDLPAR::xPositionRanking::xPositionRanking() {}

fileIndexType domainModel::xMDLPAR::xPositionRanking::numPositions()
{
    //this had better return what's actually been stored and not the max possible size
    //that is, hopefully i haven't accidentally implied to the matrix that the whole thing
    //is being used.
    return theIndices_ptr->size();
}

domainModel::xMDLPAR::xPositionRanking::positionRankingArrayType
domainModel::xMDLPAR::xPositionRanking::getPositions()
{
    return theIndices_ptr;
}


