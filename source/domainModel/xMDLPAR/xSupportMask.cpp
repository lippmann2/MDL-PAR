#include "domainModel/xMDLPAR/xSupportMask.hpp"

domainModel::xMDLPAR::xSupportMask::xSupportMask(
    domainModel::xMDLPAR::xPositionRanking thePositionRanking,
    fileIndexType theK)
    : theShortenedPositionRanking_ptr(
        new Eigen::Array<fileIndexType,Eigen::Dynamic,1>(
            (thePositionRanking.getPositions())->head(theK) ))
{
    k = theK;
    //theIndices_ptr = thePositionRanking.getPositions();
    //theShortenedPositionRanking_ptr
}

domainModel::xMDLPAR::xSupportMask::xSupportMask() {}

fileIndexType domainModel::xMDLPAR::xSupportMask::getSize()
{
    return k;
}

//might be a way to somehow make this more efficient?? no copying?
domainModel::xMDLPAR::xSupportMask::supportMaskArray_ptr
domainModel::xMDLPAR::xSupportMask::getSupportMask()
{
    //supportMaskArray_ptr
    //    theShortenedPositionRanking_ptr(new
    //        Eigen::Array<fileIndexType,Eigen::Dynamic,1,0,G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES>(
    //            theIndices_ptr->head(k)));
    //supportMaskArray_ptr
    //    theShortenedPositionRanking_ptr(new
    //        Eigen::Array<fileIndexType,Eigen::Dynamic,1>(
    //            theIndices_ptr->head(k)));


    return theShortenedPositionRanking_ptr;
}
