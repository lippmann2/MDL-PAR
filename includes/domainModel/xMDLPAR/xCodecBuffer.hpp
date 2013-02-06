#ifndef DOMAINMODEL_XMDLPAR_XCODECBUFFER_HPP
#define DOMAINMODEL_XMDLPAR_XCODECBUFFER_HPP

#include "domainModel/global.hpp"

//#include <vector> //http://www.yolinux.com/TUTORIALS/LinuxTutorialC++STL.html#VECTOR
#include <string>
#include <fstream>
#include <vector>

//#include "boost/smart_ptr/shared_ptr.hpp"

//#include "domainModel/xMDLPAR/xSymbol.hpp"
//#include "domainModel/xMDLPAR/xSymbolList.hpp"

namespace domainModel
{
    namespace xMDLPAR
    {
        class xCodecBuffer
        {
            friend class xConverter;
            friend class xContextRepository;

            public:

            //if using same buffer for compression and decompression be careful not to overwrite actual files!!!!!!!!!!
          //oh, well if pass in a string, probably assume load it into the buffer
          //if pass an int into the constructor, assume creating an empty buffer and have to save it manually later.
          //that convention should work
          xCodecBuffer();
          xCodecBuffer(const std::string& aFilePathAndName);
          //xCodecBuffer(???); //initialize from a compile-time array for testing
            //domainModel::xMDLPAR::xSymbol getSymbol(int theByteIndex);
            //boost::shared_ptr<domainModel::xMDLPAR::xSymbolList> getSymbolList(int theLowByteIndex, int theHighByteIndex);
            int getByteAsInt(fileIndexType theByteIndex) const;
            void setBufferSizeInBytes(fileIndexType theSize);
            void addByte(int theByteValue);
            fileIndexType numBytesCurrentlyInBuffer();
            void writeFile(const std::string& aFilePathAndName);


            private:
                std::string theFilePathAndName;
                fileIndexType numBytesCurrentlyStoredInBuffer;
                fileIndexType bufferSizeInBytes;

                //yes this is doubles but pretend it's bytes, as in
                //if 30 doubles are in buffer, that's 30 "bytes"
                //still thinking of them as bytes with an internal
                //representation as double
                std::vector<double> theByteBuffer; //presumably this p
        };
    }
}

#endif
