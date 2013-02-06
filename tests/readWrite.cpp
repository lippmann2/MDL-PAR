#include <iostream>
#include <string>

//#include "domainModel/global.hpp"
#include "domainModel/xMDLPAR/xCodec.hpp"

int main()
{

    unsigned long G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES = 20000000;
    double G_MAGIC_NUMBER_NORMALIZED_CONTEXT_SIMILARITY_THRESHOLD = 0.90;
    double G_MAGIC_NUMBER_NORMALIZED_SUPPORT_SIMILARITY_THRESHOLD = 0.90;

    std::string theOriginalFileNameAndPath,
        theCompressedFileNameAndPath, theDecompressedFileNameAndPath;
    theOriginalFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/ckolmogorov/ckolmogorov/tests/data/readWrite.txt";
    theCompressedFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/compressed_readWrite.out";
    theDecompressedFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/decompressed_readWrite.out";

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
