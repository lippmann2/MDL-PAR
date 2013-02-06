#ifndef DOMAINMODEL_XMDLPAR_XCONTEXT_HPP
#define DOMAINMODEL_XMDLPAR_XCONTEXT_HPP

#include "domainModel/global.hpp"

#include "boost/smart_ptr/shared_ptr.hpp"

//#include "domainModel/xMDLPAR/xConverter.hpp"

//#include "domainModel/xMDLPAR/xSymbol.hpp"
//#include "domainModel/xMDLPAR/xSymbolList.hpp"

#include "domainModel/xMDLPAR/xCodecBuffer.hpp"

//class domainModel::xMDLPAR::xSymbol;

namespace domainModel
{
  namespace xMDLPAR
  {
    class xContext
    {
        friend class xConverter;
        friend class xContextRepository;

    public:
      //static bool similarEnough(xContext A, xContext B);

        xContext();
        //xContext(fileIndexType theStartIndex,
        //         boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer> theCodecBuffer_ptr);
         xContext(fileIndexType theStartIndex, domainModel::xMDLPAR::xCodecBuffer* theCodecBuffer_ptr);
         bool isComplete() const;
      //xContext(domainModel::xMDLPAR::xSymbol theSymbol); //construct symbol's context
      //xContext(boost::shared_ptr<domainModel::xMDLPAR::xSymbolList> theSymbolList);
      //domainModel::xMDLPAR::xSymbol getKeySymbol();
      //domainModel::xMDLPAR::xSymbol getSymbolAtPosition(fileIndexType indexFromFarthest); //index 0 is farthest from key symbol
      //domainModel::xMDLPAR::xSupport getSupport(domainModel::xMDLPAR::xSupportMask theSupportMask);

    //private:
      ////200 Hz * 10 seconds * ~100 channels * 2 bytes/sample, i.e. 10 seconds of multichannel eeg
      //static const int magicNumberContextSizeInBytes = 200*10*100*2;
      bool isCompleteContext;
      fileIndexType contextStartIndex;
      //boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer> codecBuffer_ptr;
      domainModel::xMDLPAR::xCodecBuffer* codecBuffer_ptr;
    };
  }
}

#endif
