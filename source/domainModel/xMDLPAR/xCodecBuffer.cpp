#include "domainModel/xMDLPAR/xCodecBuffer.hpp"

domainModel::xMDLPAR::xCodecBuffer::xCodecBuffer(const std::string& aFilePathAndName)
{
  //http://www.cplusplus.com/reference/iostream/istream/read/
  std::ifstream is;
  is.open(aFilePathAndName.c_str(), std::ios::binary);

  //get length of file
  is.seekg(0, std::ios::end);
  numBytesCurrentlyStoredInBuffer = bufferSizeInBytes = is.tellg(); //not true yet, but in a few lines
  is.seekg(0, std::ios::beg);

  //allocate memory so code below works and no segfault
  theByteBuffer.reserve(bufferSizeInBytes);

  //read data as a block
  //vector is guaranteed to be contiguous...
  unsigned char theChar;
  for(fileIndexType i = 0; i<bufferSizeInBytes; i++)
  {
      is.read((char*)&theChar, 1);
      theByteBuffer.push_back(static_cast<double>(theChar));
  }
  //is.read( (char*)&theByteBuffer[0] , bufferSizeInBytes );

  is.close();
}

void domainModel::xMDLPAR::xCodecBuffer::writeFile(const std::string& aFilePathAndName)
{
    std::ofstream os(aFilePathAndName.c_str(), std::ios::out | std::ios::binary);
    unsigned char theChar;
    for (fileIndexType i=0; i<numBytesCurrentlyStoredInBuffer; i++)
    {
        theChar = static_cast<unsigned char>(theByteBuffer[i]);
        os.write( (char*)&theChar, 1 );
        //os.write( (char*)&theByteBuffer[0] , numBytesCurrentlyStoredInBuffer );
    }
    os.close();
}

//domainModel::xMDLPAR::xSymbol
//domainModel::xMDLPAR::xCodecBuffer::getSymbol(int theByteIndex)
//{
//    boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer> codecbuffer_ptr(this);
//  domainModel::xMDLPAR::xSymbol theSymbol(theByteBuffer->operator[](theByteIndex), theByteIndex, codecbuffer_ptr);
//  return theSymbol;
//}

//boost::shared_ptr<domainModel::xMDLPAR::xSymbolList>
//domainModel::xMDLPAR::xCodecBuffer::getSymbolList(int theLowIndex, int theHighIndex)
//{
//    boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer> tempCodecBuffer_ptr(this);
//  boost::shared_ptr<domainModel::xMDLPAR::xSymbolList> theSymbolList(new xSymbolList(theLowIndex,
//                                                                                     theHighIndex,
//                                                                                     tempCodecBuffer_ptr));
//  return theSymbolList;
//}

int domainModel::xMDLPAR::xCodecBuffer::getByteAsInt(fileIndexType theByteIndex) const
{
    //this shoudl be unit tested to make sure this cast works as expected
    assert(theByteIndex < theByteBuffer.size());
  return static_cast<int>(theByteBuffer[theByteIndex]);
}

void domainModel::xMDLPAR::xCodecBuffer::addByte(int theByteValue)
{
    //should probably be checking to make sure it's 0><256... an assert...
    numBytesCurrentlyStoredInBuffer += 1;

    //this should be unit tested to make sure this cast works as expected
    theByteBuffer.push_back(static_cast<double>(theByteValue));
}

fileIndexType domainModel::xMDLPAR::xCodecBuffer::numBytesCurrentlyInBuffer()
{
  return numBytesCurrentlyStoredInBuffer;
}

domainModel::xMDLPAR::xCodecBuffer::xCodecBuffer()
{
    //do i need to initialize that vector or is it automatic w/o an initializer list?
}

void domainModel::xMDLPAR::xCodecBuffer::setBufferSizeInBytes(fileIndexType theSize)
{
  numBytesCurrentlyStoredInBuffer = 0;
  bufferSizeInBytes = theSize;
  //theByteBuffer = boost::shared_ptr< std::vector<char> >(new std::vector<char>);
  theByteBuffer.reserve(bufferSizeInBytes);
}
