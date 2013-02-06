#include "domainModel/xMDLPAR/xContext.hpp"

domainModel::xMDLPAR::xContext::xContext() {}

//bool domainModel::xMDLPAR::xContext::similarEnough(xContext A, xContext B);
//{
//
//}
//only use when compressing (kludge)
//domainModel::xMDLPAR::xContext::xContext(domainModel::xMDLPAR::xSymbol aSymbol)
//{
//  theSymbol = aSymbol;
//  if (aSymbol.theByteIndex - magicNumberContextSizeInBytes < 0)
//    isCompleteContext = false;
//  else
//    isCompleteContext = true;
//}

//only use when decompressing (kludge)
//domainModel::xMDLPAR::xContext::xContext(domainModel::xMDLPAR::xSymbolList theSymbolList)
//{
//  if (theSymbolList.lowIndex < 0)
//    isCompleteContext = false;
//  else
//    isCompleteContext = true;
//  theContextSymbols = theSymbolList;
//}

//domainModel::xMDLPAR::xContext::xContext(
//    fileIndexType theStartIndex,
//    boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer> theCodecBuffer_ptr)
domainModel::xMDLPAR::xContext::xContext(
    fileIndexType theStartIndex,
    domainModel::xMDLPAR::xCodecBuffer* theCodecBuffer_ptr)
{
    //if (theStartIndex < 0)
    //    isCompleteContext = false;
    //else
    //    isCompleteContext = true;
    contextStartIndex = theStartIndex;
    codecBuffer_ptr = theCodecBuffer_ptr;
}

bool domainModel::xMDLPAR::xContext::isComplete() const
{
    return isCompleteContext;
}

//domainModel::xMDLPAR::xSymbol domainModel::xMDLPAR::xContext::getKeySymbol()
//{
//  return theSymbol;
//}

//domainModel::xMDLPAR::xSymbol domainModel::xMDLPAR::xContext::getSymbolAtPosition(fileIndexType indexFromFarthest)
//{
//
//}
