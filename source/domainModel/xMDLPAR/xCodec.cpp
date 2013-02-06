#include "domainModel/xMDLPAR/xCodec.hpp"

domainModel::xMDLPAR::xCodec::xCodec()
{
    #ifdef MYDEBUG
        clog.open("/mnt/local/gdrive/public/lippmann/ckolmogorov/ckolmogorov/tests/scratch/clog.txt");
    #endif
}

domainModel::xMDLPAR::xCodec::~xCodec()
{
    #ifdef MYDEBUG
        clog.close();
    #endif

}
//boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer> theCodecBuffer_ptr)
//{
//    //codecBuffer_ptr = theCodecBuffer_ptr;
//}

void domainModel::xMDLPAR::xCodec::compressTo(const std::string& theOriginalFileNameAndPath,
                                              const std::string& theCompressionFileNameAndPath)
{

    #ifdef MYDEBUG
        std::stringstream ss;
    #endif

    //boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer>
    //    codecBuffer_ptr(new domainModel::xMDLPAR::xCodecBuffer(
    //        theOriginalFileNameAndPath));

    domainModel::xMDLPAR::xCodecBuffer* codecBuffer_ptr =
        new domainModel::xMDLPAR::xCodecBuffer(theOriginalFileNameAndPath);

    domainModel::xMDLPAR::xContextRepository* contextRepository_ptr =
        new domainModel::xMDLPAR::xContextRepository();

    domainModel::xMDLPAR::xSymbolList
        entireFileOfSymbols = xConverter::toSymbolList(codecBuffer_ptr);

    domainModel::xArithCodec::xSymbolModel theSymbolModel;
    theSymbolModel.scanSymbolsForInitialScaling(entireFileOfSymbols);

    domainModel::xArithCodec::xArithEncoder theEncoder;
    theEncoder.initialize(theCompressionFileNameAndPath.c_str(),
                          codecBuffer_ptr->numBytesCurrentlyInBuffer());

    domainModel::xMDLPAR::xSymbolList theCausalSymbols;
    domainModel::xMDLPAR::xContext theSymbolContext;

    ///////////////
    domainModel::xMDLPAR::xErrorDistribution theErrorDistribution;
    domainModel::xArithCodec::xRange theRange;
    domainModel::xMDLPAR::xErrorModel theErrorModel;
    int theQuantizedPredictionError;
    domainModel::xMDLPAR::xFilterCoefficients theFilterCoefficients;
    domainModel::xMDLPAR::xSupportMask theSupportMask;
    domainModel::xMDLPAR::xPredictionComponents thePredictionComponents;
    ///////////////

    domainModel::xMDLPAR::xSymbol theCurrentSymbol;
    entireFileOfSymbols.moveToFirstSymbol();  //should never be empty, right?
    //#ifdef quickfasttest
        unsigned long symbolCount = 0;
        int a;
    //#endif

    time_t startTime = time(NULL);
    fileIndexType totalNumSymbols = codecBuffer_ptr->numBytesCurrentlyInBuffer();

    while(true)
    {
        //#ifdef COUTORLOG
        symbolCount += 1; std::cout << symbolCount << std::endl; lg << "symbol count: " << std::endl << symbolCount << std::endl;
        //#endif

        theCurrentSymbol = entireFileOfSymbols.getCurrentSymbol();
        //std::cout << "C: " << theCurrentSymbol.getValue() << std::endl;
        assert(theCurrentSymbol.byteIndex < codecBuffer_ptr->numBytesCurrentlyInBuffer());
        //theSymbolModel.addSymbol(theCurrentSymbol);

        theCausalSymbols = xConverter::toCausalSymbols(theCurrentSymbol);
        theSymbolContext = xConverter::toCausalAdjacentContext(theCurrentSymbol);

        //debug
        if (symbolCount == G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES)
        {
            a = 1;
            a = 2;
        }

        thePredictionComponents = domainModel::xMDLPAR::xPredictor::getPredictionComponents(theCausalSymbols,
                                                                                            theSymbolContext,
                                                                                            contextRepository_ptr);

        if (thePredictionComponents.meaningfulPrediction)
        {
            theErrorDistribution = thePredictionComponents.theErrorDistribution;
            theFilterCoefficients = thePredictionComponents.theFilterCoefficients;
            theSupportMask = thePredictionComponents.theSupportMask;
            theQuantizedPredictionError = domainModel::xMDLPAR::xPredictor::getError(theSupportMask, theFilterCoefficients, theSymbolContext, theCurrentSymbol);
            //std::cout << "pe: " << theQuantizedPredictionError << std::endl;
            theErrorModel = domainModel::xMDLPAR::xErrorModel(theErrorDistribution);
            theRange = theErrorModel.GetRange(theQuantizedPredictionError);
        }
        else
            theRange = theSymbolModel.GetRange(theCurrentSymbol.getValue());
        theEncoder.encodeSymbol(theRange);
        #ifdef MYDEBUG
            //ss.clear();
            //ss <
            clog << "C: " << theCurrentSymbol.getValue() << ", " << theRange.getLowAsInt() << ", " << theRange.getHighAsInt() << std::endl;
        #endif
        //lg << "C: " << theCurrentSymbol.getValue() << std::endl;
        if (entireFileOfSymbols.atLastSymbol()) break;
        entireFileOfSymbols.moveToNextSymbol();
        //#ifdef quickfasttest
            //symbolCount += 1; std::cout << symbolCount << std::endl; lg << "symbol count: " << std::endl << symbolCount << std::endl;
            //std::cout << "bw: " << bytesWritten << std::endl;

            #ifdef COUTORLOG
            std::cout << "cr: " << (1.0 * bytesWritten) / (1.0*symbolCount) << std::endl;
            fileIndexType hoursRemaining = (totalNumSymbols-symbolCount) / (symbolCount/difftime(time(NULL),startTime)) / 3600;
            std::cout << "hr: " << hoursRemaining << std::endl;
            #endif

            //if ((symbolCount % 1048576) == 0) std::cout << symbolCount
        //#endif

    }
    theEncoder.finish(theSymbolModel);

    delete codecBuffer_ptr;
    delete contextRepository_ptr;

}

void domainModel::xMDLPAR::xCodec::decompressTo(
    const std::string& theCompressedFileNameAndPath,
    const std::string& theDecompressedFileNameAndPath)
{

    //boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer>
    //    codecBuffer_ptr(new domainModel::xMDLPAR::xCodecBuffer());

    domainModel::xMDLPAR::xCodecBuffer* codecBuffer_ptr =
        new domainModel::xMDLPAR::xCodecBuffer();

    domainModel::xMDLPAR::xContextRepository* contextRepository_ptr =
        new domainModel::xMDLPAR::xContextRepository();

    domainModel::xMDLPAR::xSymbolList theSymbolList;
    domainModel::xMDLPAR::xContext theHeadContext;

    domainModel::xArithCodec::xArithDecoder theDecoder;
    theDecoder.initialize(theCompressedFileNameAndPath.c_str());
    domainModel::xArithCodec::xSymbolModel theSymbolModel(theDecoder.getSavedSymbolModel());
    theSymbolModel.rescaleAfterReloading();
    fileIndexType theDecompressedFileSize = theDecoder.getOriginalFileSizeInBytes();

    codecBuffer_ptr->setBufferSizeInBytes(theDecompressedFileSize);

    domainModel::xMDLPAR::xErrorDistribution theErrorDistribution;
    domainModel::xArithCodec::xRange theRange;
    domainModel::xMDLPAR::xErrorModel theErrorModel;
    int theQuantizedPredictionError;
    int thePredictedSymbolValue;
    int theActualSymbolValue;
    domainModel::xMDLPAR::xFilterCoefficients theFilterCoefficients;
    domainModel::xMDLPAR::xSupportMask theSupportMask;
    domainModel::xMDLPAR::xPredictionComponents thePredictionComponents;

    domainModel::xMDLPAR::xSymbol theCurrentSymbol;

    int tempSymbolCount = 0;
    while(codecBuffer_ptr->numBytesCurrentlyInBuffer() < theDecompressedFileSize)
    {
        theSymbolList = xConverter::toSymbolList(codecBuffer_ptr);
        theHeadContext = xConverter::toHeadContext(theSymbolList);

        thePredictionComponents = domainModel::xMDLPAR::xPredictor::getPredictionComponents(theSymbolList,
                                                                                            theHeadContext,
                                                                                            contextRepository_ptr);

        if (thePredictionComponents.meaningfulPrediction)
        {
            theErrorDistribution = thePredictionComponents.theErrorDistribution;
            theFilterCoefficients = thePredictionComponents.theFilterCoefficients;
            theSupportMask = thePredictionComponents.theSupportMask;
            thePredictedSymbolValue = domainModel::xMDLPAR::xPredictor::applyFilter(theFilterCoefficients, theHeadContext, theSupportMask);

            theErrorModel = domainModel::xMDLPAR::xErrorModel(theErrorDistribution);
            theQuantizedPredictionError = theDecoder.decodeSymbol(theErrorModel);
            //std::cout << "pe: " << theQuantizedPredictionError << std::endl;
            theActualSymbolValue = thePredictedSymbolValue + theQuantizedPredictionError;
        }
        else
        {
            theActualSymbolValue = theDecoder.decodeSymbol(theSymbolModel);
        }

        #ifdef COUTORLOG
        lg << "D: " << theActualSymbolValue << std::endl;
        #endif
        //theSymbolModel.addSymbol(theActualSymbolValue);
        codecBuffer_ptr->addByte(theActualSymbolValue);
        //std::cout << "D: " << tempSymbolCount << std::endl; tempSymbolCount++;
    }

    theDecoder.finish();
    codecBuffer_ptr->writeFile(theDecompressedFileNameAndPath);
    delete codecBuffer_ptr;
    delete contextRepository_ptr;

}

bool domainModel::xMDLPAR::xCodec::theFilesAreEquivalent(const std::string& theOriginalFileNameAndPath,
                                      const std::string& theDecompressedFileNameAndPath)
{
    FILE* a; FILE* b;
    a = std::fopen(theOriginalFileNameAndPath.c_str(), "rb");
    b = std::fopen(theDecompressedFileNameAndPath.c_str(), "rb");
    if (a ==NULL || b==NULL)
    {
        if (a!=NULL) fclose(a);
        if (b!=NULL) fclose(b);
    }
    fseek(a,0,SEEK_END); fileIndexType aSize = ftell(a);
    fseek(b,0,SEEK_END); fileIndexType bSize = ftell(b);
    if (aSize != bSize)
    {
        fclose(a);
        fclose(b);
        return false;
    }
    rewind(a); rewind(b);
    fileIndexType byteCount = 0;
    int c;
    do
    {
        c = getc(a);
        byteCount++;
        if (getc(b)!=c)
        {
            fclose(a);fclose(b);
            return false;
        }
    } while(c!=EOF);

    fclose(a);
    fclose(b);
    return true;
}
