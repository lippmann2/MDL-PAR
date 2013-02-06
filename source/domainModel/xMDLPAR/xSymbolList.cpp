#include "domainModel/xMDLPAR/xSymbolList.hpp"

//domainModel::xMDLPAR::xSymbolList::xSymbolList(
//    fileIndexType theLowByteIndex, fileIndexType theHighByteIndex,
//    boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer> theCodecBuffer_ptr)
domainModel::xMDLPAR::xSymbolList::xSymbolList(
    fileIndexType theLowByteIndex, fileIndexType theHighByteIndex,
    domainModel::xMDLPAR::xCodecBuffer* theCodecBuffer_ptr)
{
  lowIndex = theLowByteIndex;
  highIndex = theHighByteIndex;
  codecBuffer_ptr = theCodecBuffer_ptr;
}

//domainModel::xMDLPAR::xSymbol domainModel::xMDLPAR::xSymbolList::getASymbol(fileIndexType theRelativeByteIndex)
//{
//  fileIndexType theAbsoluteByteIndex = theLowByteIndex + theRelativeByteIndex;
//  return domainModel::xMDLPAR::xSymbol(codecBuffer[theAbsoluteByteIndex], theAbsoluteByteIndex, codecBuffer);
//}

bool domainModel::xMDLPAR::xSymbolList::isEmpty() const
{
    //bool emptyList = false;
    //if (lowIndex > highIndex)
    //    emptyList = true;
    return !nonEmptyList;
    //return (numSymbols() == 0);
}

domainModel::xMDLPAR::xSymbolList::xSymbolList() {}

fileIndexType domainModel::xMDLPAR::xSymbolList::numSymbols()
{
  if (!nonEmptyList) return 0;
  return highIndex - lowIndex + 1;
}

void domainModel::xMDLPAR::xSymbolList::moveToFirstSymbol()
{
  currentRelativeIndex = 0;
}

void domainModel::xMDLPAR::xSymbolList::moveToNextSymbol()
{
  if (currentRelativeIndex < highIndex)
    currentRelativeIndex += 1;
}

bool domainModel::xMDLPAR::xSymbolList::atLastSymbol()
{
  if (currentRelativeIndex >= highIndex)
    return true;
  else
    return false;
}

domainModel::xMDLPAR::xSymbol domainModel::xMDLPAR::xSymbolList::getCurrentSymbol()
{
  fileIndexType theAbsoluteByteIndex = lowIndex + currentRelativeIndex;
  domainModel::xMDLPAR::xSymbol theSymbol =
    domainModel::xMDLPAR::xSymbol(theAbsoluteByteIndex, codecBuffer_ptr);
  //alternative syntax?:
  //domainModel::xMDLPAR::xSymbol theSymbol(theAbsoluteByteIndex, codecBuffer_ptr);
  return theSymbol;
}

//domainModel::xMDLPAR::xContext domainModel::xMDLPAR::xSymbolList::getHeadContext()
//{
//  fileIndexType theLow = theHighByteIndex - magicNumberContextSizeInBytes + 1;
//  fileIndexType theHigh = highIndex;
//  return domainModel::xMDLPAR::xContext(domainModel::xMDLPAR::xSymbolList(theLow, theHigh, codecBuffer));
//}
