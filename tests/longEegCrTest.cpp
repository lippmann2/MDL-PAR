#include <iostream>
#include <string>

#include "domainModel/xMDLPAR/xCodec.hpp"

unsigned long G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES;
double G_MAGIC_NUMBER_NORMALIZED_CONTEXT_SIMILARITY_THRESHOLD;
double G_MAGIC_NUMBER_NORMALIZED_SUPPORT_SIMILARITY_THRESHOLD;
int G_MAGIC_NUMBER_NUM_APPROX_NEIGHBORS_TO_CHECK;

std::ofstream lg;
fileIndexType bytesWritten;

int main()
{

  G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES = 10;
  G_MAGIC_NUMBER_NORMALIZED_CONTEXT_SIMILARITY_THRESHOLD = 0.60;
  G_MAGIC_NUMBER_NORMALIZED_SUPPORT_SIMILARITY_THRESHOLD = 0.60;
  G_MAGIC_NUMBER_NUM_APPROX_NEIGHBORS_TO_CHECK = 100; //could put back to ten to speed up. plus haven't added the primes
  setup();
  assert(G_MAGIC_NUMBER_MAX_RAW_CONTEXT_DISTANCE > 0);

    std::string theOriginalFileNameAndPath,
        theCompressedFileNameAndPath, theDecompressedFileNameAndPath;
    theOriginalFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/network-inference/trunk/seizureExtraction/37__CHOP374d__070125.0.mat";
    theCompressedFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/eegL_compressed.out";
    theDecompressedFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/eegL_decompressed.out";

    domainModel::xMDLPAR::xCodec theCodec;
    theCodec.compressTo(theOriginalFileNameAndPath, theCompressedFileNameAndPath);
    theCodec.decompressTo(theCompressedFileNameAndPath, theDecompressedFileNameAndPath);
    bool passed = theCodec.theFilesAreEquivalent(theOriginalFileNameAndPath, theDecompressedFileNameAndPath);

    std::string passMessage;
    //std::cout << std::endl;
    if (passed)
        passMessage = "PASSED Lenna";
    else
        passMessage = "FAILED Lenna";
    std::cout << passMessage << std::endl;

}
