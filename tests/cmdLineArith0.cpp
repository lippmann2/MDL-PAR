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

int main(int argc, char* argv[])
{

    //don't forget atoi[]
    //http://www.site.uottawa.ca/~lucia/courses/2131-05/labs/Lab3/CommandLineArguments.html

  G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES = 2294967296; //~2GB, should make all other params meaningless
  G_MAGIC_NUMBER_NORMALIZED_CONTEXT_SIMILARITY_THRESHOLD = 0.85;
  G_MAGIC_NUMBER_NORMALIZED_SUPPORT_SIMILARITY_THRESHOLD = 0.85;
  //G_MAGIC_NUMBER_NUM_APPROX_NEIGHBORS_TO_CHECK = 1000; //could put back to ten to speed up. plus haven't added the primes
  //G_MAGIC_NUMBER_MAX_NUM_NEIGHBORS_TO_USE = 100;
  G_MAGIC_NUMBER_NUM_APPROX_NEIGHBORS_TO_CHECK = 2294967296+1;
  G_MAGIC_NUMBER_MAX_NUM_NEIGHBORS_TO_USE = 2294967296+1;

  setup();
  assert(G_MAGIC_NUMBER_MAX_RAW_CONTEXT_DISTANCE > 0);

    assert(G_MAGIC_NUMBER_MAX_NUM_NEIGHBORS_TO_USE > G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES); //????

    std::string theOriginalFileNameAndPath,
        theCompressedFileNameAndPath, theDecompressedFileNameAndPath;
    theOriginalFileNameAndPath = argv[1];
        //"/mnt/local/gdrive/public/lippmann/ckolmogorov/ckolmogorov/tests/data/Lenna_grayscale.bin";
    theCompressedFileNameAndPath = argv[2];
        //"/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/glenna_compressed.out";
    //theDecompressedFileNameAndPath = argv[3];
        //"/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/glenna_decompressed.out";

    domainModel::xMDLPAR::xCodec theCodec;
    //lg.open(argv[4]); //"/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/lenna_lg_c.txt");
    theCodec.compressTo(theOriginalFileNameAndPath, theCompressedFileNameAndPath);
    //lg.close();
    //theCodec.decompressTo(theCompressedFileNameAndPath, theDecompressedFileNameAndPath);
    //bool passed = theCodec.theFilesAreEquivalent(theOriginalFileNameAndPath, theDecompressedFileNameAndPath);

    //std::string passMessage;
    //std::cout << std::endl;
    //if (passed)
    //    passMessage = "PASSED Lenna";
    //else
    //    passMessage = "FAILED Lenna";
    //std::cout << passMessage << std::endl;

}
