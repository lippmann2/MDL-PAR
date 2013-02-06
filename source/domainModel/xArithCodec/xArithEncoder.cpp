//Adapted from The Data Compression Book 2nd Ed.

#include "domainModel/xArithCodec/xArithEncoder.hpp"

domainModel::xArithCodec::xArithEncoder::xArithEncoder() {}

void domainModel::xArithCodec::xArithEncoder::initialize(const char* theOutputFileNameAndPath,
                                                         fileIndexType numBytesCurrentlyInBuffer)
{
    output = OpenOutputBitFile(theOutputFileNameAndPath);
    //if ( output == NULL )
    //    fatal_error("Error opening %s for output\n", theOutputFileNameAndPath );
    ////////////
    fileSizeToBeEncoded = numBytesCurrentlyInBuffer;

    outputFileNameAndPath = theOutputFileNameAndPath;
    ////////////


    low = 0;
    high = 0xffff;
    underflow_bits = 0;

}

void domainModel::xArithCodec::xArithEncoder::encodeSymbol(domainModel::xArithCodec::xRange theRange)
{
    s.low_count = theRange.getLowAsInt();
    s.high_count = theRange.getHighAsInt();
    s.scale = theRange.getScaleAsInt();
    encode_symbol(output, &s);
}

void domainModel::xArithCodec::xArithEncoder::finish(domainModel::xArithCodec::xSymbolModel theSymbolModel)
{
    //don't need this because keep symbol count
    //convert_int_to_symbol( END_OF_STREAM, &s );
    //encode_symbol( output, &s );

    flush_arithmetic_encoder( output );
    OutputBits( output, 0L, 16 );
    //////////////
    //well crap, now I have to write to space reserved at the beginning of the file???
    //i could just put it all at the end
    //and the decoder would know to do stuff with the last X bits
    CloseOutputBitFile(output);

    std::fstream outFile(outputFileNameAndPath, std::ios::in | std::ios::out | std::ios::binary | std::ios::ate | std::ios::app);

    ////test
    //outFile.write("#$%",3);

    outFile.write((char*)&fileSizeToBeEncoded, fileIndexTypeSize);

    //AlignToBoundary(output);

    ////test
    //outFile.write("#$%",3);

    //the original file size:
    //OutputBits(output, (unsigned long)fileSizeToBeEncoded, sizeof(unsigned long)*8);

    //save symbolModel, skipping the original 0 count. should be 257 slots,
    unsigned char tempVal;
    //fileIndexType tempVal;
    for (int i = 0; i<=255; i++)
    {
        tempVal = (unsigned char)theSymbolModel.getSymbolCount(i);
        outFile.write((char*)&tempVal,sizeof(unsigned char));

        //tempVal = (fileIndexType)theSymbolModel.getSymbolCount(i);
        //outFile.write((char*)&tempVal,fileIndexTypeSize);

        //OutputBits(output, (unsigned long)theSymbolModel.getSymbolCount(i), sizeof(unsigned long)*8);
    }
    //////////////

    outFile.close();
    //CloseOutputBitFile(output);
}

void domainModel::xArithCodec::xArithEncoder::encode_symbol( BIT_FILE *stream, SYMBOL *s )
{
  long range;
 /*
  * These three lines rescale high and low for the new symbol.
  */
  range = (long) ( high-low ) + 1;
  high = low + (unsigned short int) (( range * s->high_count ) / s->scale - 1 );
  low = low + (unsigned short int) (( range * s->low_count ) / s->scale );
 /*
  * This loop turns out new bits until high and low are far enough
  * apart to have stabilized.
  */
  for ( ; ; ) {
   /*
    * If this test passes, it means that the MSDigits match, and can
    * be sent to the output stream.
    */
    if ( ( high & 0x8000 ) == ( low & 0x8000 ) ) {
      OutputBit( stream, high & 0x8000 );
      while ( underflow_bits > 0 ) {
        OutputBit( stream, ~high & 0x8000 );
        underflow_bits--;
      }
    }
   /*
    * If this test passes, the numbers are in danger of underflow, because
    * the MSDigits don't match, and the 2nd digits are just one apart.
    */
    else if ( ( low & 0x4000 ) && !( high & 0x4000 )) {
      underflow_bits += 1;
      low &= 0x3fff;
      high |= 0x4000;
    } else
        return ;
    low <<= 1;
    high <<= 1;
    high |= 1;
  }
}

/*
 * At the end of the encoding process, there are still significant
 * bits left in the high and low registers.  We output two bits,
 * plus as many underflow bits as are necessary.
 */
void domainModel::xArithCodec::xArithEncoder::flush_arithmetic_encoder(BIT_FILE *stream )
{
  OutputBit( stream, low & 0x4000 );
  underflow_bits++;
  while ( underflow_bits-- > 0 )
    OutputBit( stream, ~low & 0x4000 );
}

