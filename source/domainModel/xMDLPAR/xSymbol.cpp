#include "domainModel/xMDLPAR/xSymbol.hpp"
//#include "domainModel/xMDLPAR/xContext.hpp"

//domainModel::xMDLPAR::xSymbol::xSymbol(int theSymbolValue, fileIndexType theByteIndex, domainModel::xMDLPAR::xCodecBuffer theBuffer)
//{
//  symbolValue = theSymbolValue;
//    byteIndex = theByteIndex;
//    codecBuffer = theBuffer;
//}

domainModel::xMDLPAR::xSymbol::xSymbol() {}

//domainModel::xMDLPAR::xSymbol::xSymbol(fileIndexType theByteIndex, boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer> theCodecBuffer_ptr)
domainModel::xMDLPAR::xSymbol::xSymbol(fileIndexType theByteIndex, domainModel::xMDLPAR::xCodecBuffer* theCodecBuffer_ptr)
{
    byteIndex = theByteIndex;
    codecBuffer_ptr = theCodecBuffer_ptr;
}

int domainModel::xMDLPAR::xSymbol::getValue()
{
    return codecBuffer_ptr->getByteAsInt(byteIndex);
}

//int domainModel::xMDLPAR::xSymbol::getSymbolAsInt() const {return symbolValue;}

//domainModel::xMDLPAR::xContext domainModel::xMDLPAR::xSymbol::getSymbolContext()
//{
//  return domainModel::xMDLPAR::xContext(this);
//}
