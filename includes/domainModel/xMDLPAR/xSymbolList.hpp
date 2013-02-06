#ifndef DOMAINMODEL_XMDLPAR_XSYMBOLLIST_HPP
#define DOMAINMODEL_XMDLPAR_XSYMBOLLIST_HPP

#include "domainModel/global.hpp"

#include "boost/smart_ptr/shared_ptr.hpp"

//#include "domainModel/xMDLPAR/xConverter.hpp"
#include "domainModel/xMDLPAR/xSymbol.hpp"
//#include "domainModel/xMDLPAR/xContext.hpp"
#include "domainModel/xMDLPAR/xCodecBuffer.hpp"



namespace domainModel
{
  namespace xMDLPAR
  {
    class xSymbolList
    {
        friend class xConverter;

    public:
        xSymbolList();
        //xSymbolList(fileIndexType theLowByteIndex, fileIndexType theHighByteIndex,
        //            boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer> theCodecBuffer_ptr);
        xSymbolList(fileIndexType theLowByteIndex, fileIndexType theHighByteIndex,
                    domainModel::xMDLPAR::xCodecBuffer* theCodecBuffer_ptr);

        fileIndexType numSymbols();
        void moveToFirstSymbol();
        bool atLastSymbol();
        bool isEmpty() const;
        void moveToNextSymbol();
        domainModel::xMDLPAR::xSymbol getCurrentSymbol();
        //domainModel::xMDLPAR::xContext getHeadContext();

    private:
        fileIndexType lowIndex;
        fileIndexType highIndex;
        fileIndexType currentRelativeIndex;
        bool nonEmptyList;
        //boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer> codecBuffer_ptr;
        domainModel::xMDLPAR::xCodecBuffer* codecBuffer_ptr;
    };
  }
}

#endif
