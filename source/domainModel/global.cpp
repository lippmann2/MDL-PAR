#include "domainModel/global.hpp"

/////200 Hz * 10 seconds * ~100 channels * 2 bytes/sample, i.e. 10 seconds of multichannel eeg

/////
//const int G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES = 96000; //=200*2*120*2; //alternatively see below
/////
//const int G_MAGIC_NUMBER_MAX_SYMBOL_VALUE = 255;

vectorType thePrimes;


double G_MAGIC_NUMBER_MAX_RAW_CONTEXT_DISTANCE;

//lg.open("/mnt/local/gdrive/public/lipp")

void setup()
{

    bytesWritten = 0;
    G_MAGIC_NUMBER_MAX_RAW_CONTEXT_DISTANCE =
        std::sqrt(G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES * std::pow(G_MAGIC_NUMBER_MAX_SYMBOL_VALUE,2));

    FILE* pFile;
    pFile = std::fopen("/mnt/local/gdrive/public/lippmann/ckolmogorov/ckolmogorov/data/primes.bin" ,"rb");
    fseek(pFile,0,SEEK_END);
    fileIndexType fileSize = ftell(pFile);
    fseek(pFile,0,SEEK_SET);
    double* thePrimeArray = new double[fileSize/sizeof(double)];
    fread(thePrimeArray,sizeof(double),fileSize/sizeof(double),pFile);
    thePrimes = vectorType(fileSize/sizeof(double));
    for (fileIndexType i = 0; i<fileSize/sizeof(double); i++)
    {
        thePrimes(i) = thePrimeArray[i];
    }
    assert(thePrimes(fileSize/sizeof(double)-1) == 4256227);
    delete[] thePrimeArray;
}
//const double G_MAGIC_NUMBER_NORMALIZED_CONTEXT_SIMILARITY_THRESHOLD = 0.90;
//const double G_MAGIC_NUMBER_NORMALIZED_SUPPORT_SIMILARITY_THRESHOLD = 0.90;


//alternatively like 1 second of eeg a la delta, maybe 2 seconds
//200 Hz * 2 seconds * ~120 channels, * 2 bytes/sample ***
