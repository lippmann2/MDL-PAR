#ifndef DOMAINMODEL_XMDLPAR_XSYMBOL_HPP
#define DOMAINMODEL_XMDLPAR_XSYMBOL_HPP

#include "domainModel/global.hpp"

#include "boost/smart_ptr/shared_ptr.hpp"

#include "domainModel/xMDLPAR/xCodecBuffer.hpp"
//#include "domainModel/xMDLPAR/xContext.hpp"
//#include "domainModel/xMDLPAR/xSymbolList.hpp"

namespace domainModel
{
    namespace xMDLPAR
    {
        class xSymbol
        {
            friend class xConverter;

            public:
        xSymbol();
		//xSymbol(fileIndexType theByteIndex, boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer> theCodecBuffer_ptr);
		xSymbol(fileIndexType theByteIndex, domainModel::xMDLPAR::xCodecBuffer* theCodecBuffer_ptr);
		int getValue();
		//xSymbol(int theSymbolValue, fileIndexType theByteIndex, boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer> theBuffer);
		//int getSymbolAsInt() const;
		//domainModel::xMDLPAR::xContext getSymbolContext();
		//friend class domainModel::xMDLPAR::xContext;
		//friend class domainModel::xMDLPAR::xSymbolList;
            //private:
                //int symbolValue;
		fileIndexType byteIndex;
		//boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer> codecBuffer_ptr;
        domainModel::xMDLPAR::xCodecBuffer* codecBuffer_ptr;
        };
    }
}

#endif
