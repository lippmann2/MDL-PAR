//Adapted from The Data Compression Book 2nd Ed.

#include "domainModel/xArithCodec/xArithDecoder.hpp"

domainModel::xArithCodec::xArithDecoder::xArithDecoder() {}

void domainModel::xArithCodec::xArithDecoder::initialize(
    const char* theFileToBeDecompressedFileNameAndPath) //, char* theOutputFileNameAndPath)
{
    /////////////////
    //get what's needed from the end of the file...
    FILE* pFile;
    pFile = std::fopen(theFileToBeDecompressedFileNameAndPath, "rb");

    fseek(pFile,0,SEEK_END);
    fileIndexType fileSize = ftell(pFile);

    //test
    //for (fileIndexType i = 0; i<=1000; i++)
    //{
    //    fseek(pFile,i,SEEK_SET);
    //    fread(&originalFileSizeInBytes,fileIndexTypeSize,1,pFile);
    //    if (originalFileSizeInBytes == 432)
    //        int a=1;
    //}

    fseek(pFile,fileSize - fileIndexTypeSize - (256*sizeof(unsigned char)),SEEK_SET);
    //fseek(pFile, fileSize - 257*fileIndexTypeSize, SEEK_SET);
    fread(&originalFileSizeInBytes, fileIndexTypeSize, 1, pFile);

    //fileIndexType tempSymbolCount;
    unsigned char tempSymbolCount;
    for (fileIndexType i = 0; i<=255; i++)
    {
        fread(&tempSymbolCount, sizeof(unsigned char), 1, pFile);
        savedSymbolModel.setSymbolCount(i,(fileIndexType)tempSymbolCount);
        //fread(&tempSymbolCount, fileIndexTypeSize,1, pFile);
        //savedSymbolModel.setSymbolCount(i,tempSymbolCount);
    }

    fclose(pFile);
    /////////////////


    input = OpenInputBitFile(theFileToBeDecompressedFileNameAndPath);
    //output = fopen(theOutputFileNameAndPath,"wb");
    initialize_arithmetic_decoder(input);

    #ifdef MYDEBUG
        dlog.open("/mnt/local/gdrive/public/lippmann/ckolmogorov/ckolmogorov/tests/scratch/dlog.txt");
    #endif

}

//keeping output in two places at the moment to predict and write out, which is inefficent
//but one thing at a time.//
int domainModel::xArithCodec::xArithDecoder::decodeSymbol(domainModel::xArithCodec::xModel& theModel)
{

    short int theScale = theModel.getScale();

  long range;
  short int count;
  range = (long) ( high - low ) + 1;
  count = (short int) ((((long) ( code - low ) + 1 ) * theScale-1 ) / range );
  assert(low<=high);
  assert(code>=low);

    int theSymbolValue = theModel.GetSymbolValue(count);
    domainModel::xArithCodec::xRange theRange = theModel.GetRange(theSymbolValue);
    s.scale = theScale;
    s.low_count = (short int) theRange.getLowAsInt();
    s.high_count = (short int) theRange.getHighAsInt();

  remove_symbol_from_stream( input, &s );

  #ifdef MYDEBUG
    dlog << "D: " << theSymbolValue << ", " << s.low_count << ", " << s.high_count << std::endl;
  #endif


  return theSymbolValue;
}

void domainModel::xArithCodec::xArithDecoder::finish()
{
    CloseInputBitFile( input );
    #ifdef MYDEBUG
        dlog.close();
    #endif
    //fclose( output );
}

/*
 * This routine is called to initialize the state of the arithmetic
 * decoder.  This involves initializing the high and low registers
 * to their conventional starting values, plus reading the first
 * 16 bits from the input stream into the code value.
 */
void domainModel::xArithCodec::xArithDecoder::initialize_arithmetic_decoder( BIT_FILE *stream )
{
  int i;

  code = 0;
  for ( i = 0 ; i < 16 ; i++ ) {
    code <<= 1;
    code += InputBit( stream );
  }
  low = 0;
  high = 0xffff;
}

void domainModel::xArithCodec::xArithDecoder::remove_symbol_from_stream(BIT_FILE *stream, SYMBOL *s)
{
  long range;

 /*
  * First, the range is expanded to account for the symbol removal.
  */
  range = (long)( high - low ) + 1;
  high = low + (unsigned short int) (( range * s->high_count ) / s->scale - 1 );
  low = low + (unsigned short int) (( range * s->low_count ) / s->scale );
 /*
  * Next, any possible bits are shipped out.
  */
  for ( ; ; ) {
  /*
   * If the MSDigits match, the bits will be shifted out.
   */
   if ( ( high & 0x8000 ) == ( low & 0x8000 ) ) {} /* intentionally left blank...*/
  /*
   * Else, if underflow is threatening, shift out the 2nd MSDigit.
   */
   else if ((low & 0x4000) == 0x4000  && (high & 0x4000) == 0 ) {
     code ^= 0x4000;
     low   &= 0x3fff;
     high  |= 0x4000;
   } else
     /*
      * Otherwise, nothing can be shifted out, so I return.
      */
      return;
   low <<= 1;
   high <<= 1;
   high |= 1;
   code <<= 1;
   code += InputBit( stream );
  }
}

domainModel::xArithCodec::xSymbolModel
domainModel::xArithCodec::xArithDecoder::getSavedSymbolModel()
{
    return savedSymbolModel;
}

fileIndexType domainModel::xArithCodec::xArithDecoder::getOriginalFileSizeInBytes()
{
    return originalFileSizeInBytes;
}
