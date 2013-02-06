#include <iostream>
#include <string>

//#include "domainModel/global.hpp"
#include "domainModel/xMDLPAR/xCodec.hpp"

const unsigned long G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES = 20000000;
const double G_MAGIC_NUMBER_NORMALIZED_CONTEXT_SIMILARITY_THRESHOLD = 0.90;
const double G_MAGIC_NUMBER_NORMALIZED_SUPPORT_SIMILARITY_THRESHOLD = 0.90;

int main()
{

    std::string theOriginalFileNameAndPath,
        theCompressedFileNameAndPath, theDecompressedFileNameAndPath;
    theOriginalFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/network-inference/trunk/seizureExtraction/37__CHOP374d__070125.0.mat";
    theCompressedFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/compressed_CHOP_debugLongNoPG_03.out";
    theDecompressedFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/decompressed_CHOP_debugLongNoPG_03.out";

    domainModel::xMDLPAR::xCodec theCodec;
    theCodec.compressTo(theOriginalFileNameAndPath, theCompressedFileNameAndPath);
    theCodec.decompressTo(theCompressedFileNameAndPath, theDecompressedFileNameAndPath);
    bool passed = theCodec.theFilesAreEquivalent(theOriginalFileNameAndPath, theDecompressedFileNameAndPath);

    std::string passMessage;
    std::cout << std::endl;
    if (passed)
        passMessage = "PASSED";
    else
        passMessage = "FAILED";
    std::cout << passMessage << std::endl;

}
