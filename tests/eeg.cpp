#include <iostream>
#include <string>

#include "domainModel/xMDLPAR/xCodec.hpp"

unsigned long G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES;
double G_MAGIC_NUMBER_NORMALIZED_CONTEXT_SIMILARITY_THRESHOLD;
double G_MAGIC_NUMBER_NORMALIZED_SUPPORT_SIMILARITY_THRESHOLD;
int G_MAGIC_NUMBER_NUM_APPROX_NEIGHBORS_TO_CHECK;
fileIndexType G_MAGIC_NUMBER_MAX_NUM_NEIGHBORS_TO_USE;

std::ofstream lg;
fileIndexType bytesWritten;

int main()
{

  G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES = 10;//10;
  G_MAGIC_NUMBER_NORMALIZED_CONTEXT_SIMILARITY_THRESHOLD = 0.85;
  G_MAGIC_NUMBER_NORMALIZED_SUPPORT_SIMILARITY_THRESHOLD = 0.95;
  G_MAGIC_NUMBER_NUM_APPROX_NEIGHBORS_TO_CHECK = 2000; //could put back to ten to speed up. plus haven't added the primes
  G_MAGIC_NUMBER_MAX_NUM_NEIGHBORS_TO_USE = 240;
  setup();
  assert(G_MAGIC_NUMBER_MAX_RAW_CONTEXT_DISTANCE > 0);

    assert(G_MAGIC_NUMBER_MAX_NUM_NEIGHBORS_TO_USE > G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES); //????

    std::string theOriginalFileNameAndPath,
        theCompressedFileNameAndPath, theDecompressedFileNameAndPath;
    theOriginalFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/ckolmogorov/ckolmogorov/tests/data/18__chop18_01e_cut__083316.bin";
    theCompressedFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/18__chop18_01e_cut__083316.bin_compressed.out";
    theDecompressedFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/18__chop18_01e_cut__083316.bin_decompressed.out";

    domainModel::xMDLPAR::xCodec theCodec;
    lg.open("/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/18__chop18_01e_cut__083316.bin_lg_c.txt");
    theCodec.compressTo(theOriginalFileNameAndPath, theCompressedFileNameAndPath);
    lg.close();
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
