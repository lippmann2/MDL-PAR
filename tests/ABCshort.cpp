#include <iostream>
#include <string>

#include "domainModel/xMDLPAR/xCodec.hpp"

unsigned long G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES;
double G_MAGIC_NUMBER_NORMALIZED_CONTEXT_SIMILARITY_THRESHOLD;
double G_MAGIC_NUMBER_NORMALIZED_SUPPORT_SIMILARITY_THRESHOLD;
int G_MAGIC_NUMBER_NUM_APPROX_NEIGHBORS_TO_CHECK;

void shortABC()
{

  G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES = 3;
  G_MAGIC_NUMBER_NORMALIZED_CONTEXT_SIMILARITY_THRESHOLD = 0.90;
  G_MAGIC_NUMBER_NORMALIZED_SUPPORT_SIMILARITY_THRESHOLD = 0.90;
  G_MAGIC_NUMBER_NUM_APPROX_NEIGHBORS_TO_CHECK = 10;
  setup();
  assert(G_MAGIC_NUMBER_MAX_RAW_CONTEXT_DISTANCE > 0);

    std::string theOriginalFileNameAndPath,
        theCompressedFileNameAndPath, theDecompressedFileNameAndPath;
    theOriginalFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/ckolmogorov/ckolmogorov/tests/data/ABC.txt";
    theCompressedFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/compressed_ABC.out";
    theDecompressedFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/decompressed_ABC.out";

    domainModel::xMDLPAR::xCodec theCodec;
    theCodec.compressTo(theOriginalFileNameAndPath, theCompressedFileNameAndPath);
    theCodec.decompressTo(theCompressedFileNameAndPath, theDecompressedFileNameAndPath);
    bool passed = theCodec.theFilesAreEquivalent(theOriginalFileNameAndPath, theDecompressedFileNameAndPath);

    std::string passMessage;
    //std::cout << std::endl;
    if (passed)
        passMessage = "PASSED shortABC";
    else
        passMessage = "FAILED shortABC";
    std::cout << passMessage << std::endl;

}


int main()
{
    std::cout << std::endl;
    //quickishArith0();
    quickishMDLPAR();
}
