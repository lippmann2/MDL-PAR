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

#define COUTORLOG

int quickishMDLPAR()
{

  G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES = 3;
  G_MAGIC_NUMBER_NORMALIZED_CONTEXT_SIMILARITY_THRESHOLD = 0.90;
  G_MAGIC_NUMBER_NORMALIZED_SUPPORT_SIMILARITY_THRESHOLD = 0.90;
  G_MAGIC_NUMBER_NUM_APPROX_NEIGHBORS_TO_CHECK = 10;
  G_MAGIC_NUMBER_MAX_NUM_NEIGHBORS_TO_USE = 5;
  setup();
  assert(G_MAGIC_NUMBER_MAX_RAW_CONTEXT_DISTANCE > 0);

    std::string theOriginalFileNameAndPath,
        theCompressedFileNameAndPath, theDecompressedFileNameAndPath;
    theOriginalFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/ckolmogorov/ckolmogorov/tests/data/ABClonger.txt";
    theCompressedFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/compressed_ABClonger.out";
    theDecompressedFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/decompressed_ABClonger.out";

    domainModel::xMDLPAR::xCodec theCodec;
    theCodec.compressTo(theOriginalFileNameAndPath, theCompressedFileNameAndPath);
    theCodec.decompressTo(theCompressedFileNameAndPath, theDecompressedFileNameAndPath);
    bool passed = theCodec.theFilesAreEquivalent(theOriginalFileNameAndPath, theDecompressedFileNameAndPath);

    std::string passMessage;
    //std::cout << std::endl;
    if (passed)
        passMessage = "PASSED quickishMDLPAR";
    else
        passMessage = "FAILED quickishMDLPAR";
    std::cout << passMessage << std::endl;
    if (passed)
        return 0;
    else
        return 1;

}

int aaab()
{

  G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES = 20000000;
  G_MAGIC_NUMBER_NORMALIZED_CONTEXT_SIMILARITY_THRESHOLD = 0.90;
  G_MAGIC_NUMBER_NORMALIZED_SUPPORT_SIMILARITY_THRESHOLD = 0.90;
  G_MAGIC_NUMBER_NUM_APPROX_NEIGHBORS_TO_CHECK = 10;
  G_MAGIC_NUMBER_MAX_NUM_NEIGHBORS_TO_USE = 5;
  setup();
  assert(G_MAGIC_NUMBER_MAX_RAW_CONTEXT_DISTANCE > 0);

    std::string theOriginalFileNameAndPath,
        theCompressedFileNameAndPath, theDecompressedFileNameAndPath;
    theOriginalFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/ckolmogorov/ckolmogorov/tests/data/aaab.txt";
    theCompressedFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/compressed_aaab.out";
    theDecompressedFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/decompressed_aaab.out";

    domainModel::xMDLPAR::xCodec theCodec;
    theCodec.compressTo(theOriginalFileNameAndPath, theCompressedFileNameAndPath);
    theCodec.decompressTo(theCompressedFileNameAndPath, theDecompressedFileNameAndPath);
    bool passed = theCodec.theFilesAreEquivalent(theOriginalFileNameAndPath, theDecompressedFileNameAndPath);

    std::string passMessage;
    //std::cout << std::endl;
    if (passed)
        passMessage = "PASSED aaab need to factor in compression ratio";
    else
        passMessage = "FAILED aaab need to factor in compression ratio";
    std::cout << passMessage << std::endl;

    if (passed)
        return 0;
    else
        return 1;

}

int quickishArith0()
{

  G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES = 20000000;
  G_MAGIC_NUMBER_NORMALIZED_CONTEXT_SIMILARITY_THRESHOLD = 0.90;
  G_MAGIC_NUMBER_NORMALIZED_SUPPORT_SIMILARITY_THRESHOLD = 0.90;
  G_MAGIC_NUMBER_NUM_APPROX_NEIGHBORS_TO_CHECK = 10;
  G_MAGIC_NUMBER_MAX_NUM_NEIGHBORS_TO_USE = 5;
  setup();
  assert(G_MAGIC_NUMBER_MAX_RAW_CONTEXT_DISTANCE > 0);

    std::string theOriginalFileNameAndPath,
        theCompressedFileNameAndPath, theDecompressedFileNameAndPath;
    theOriginalFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/ckolmogorov/ckolmogorov/tests/data/tinyFile2.txt";
    theCompressedFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/compressed.out";
    theDecompressedFileNameAndPath =
        "/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/decompressed.out";

    domainModel::xMDLPAR::xCodec theCodec;
    theCodec.compressTo(theOriginalFileNameAndPath, theCompressedFileNameAndPath);
    theCodec.decompressTo(theCompressedFileNameAndPath, theDecompressedFileNameAndPath);
    bool passed = theCodec.theFilesAreEquivalent(theOriginalFileNameAndPath, theDecompressedFileNameAndPath);

    std::string passMessage;
    //std::cout << std::endl;
    if (passed)
        passMessage = "PASSED quickishArith0";
    else
        passMessage = "FAILED quickishArith0";
    std::cout << passMessage << std::endl;

    if (passed)
        return 0;
    else
        return 1;

}

int shortABC()
{

  G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES = 3;
  G_MAGIC_NUMBER_NORMALIZED_CONTEXT_SIMILARITY_THRESHOLD = 0.99;
  G_MAGIC_NUMBER_NORMALIZED_SUPPORT_SIMILARITY_THRESHOLD = 0.99;
  G_MAGIC_NUMBER_NUM_APPROX_NEIGHBORS_TO_CHECK = 10;
  G_MAGIC_NUMBER_MAX_NUM_NEIGHBORS_TO_USE = 5;
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
    lg.open("/mnt/local/gdrive/public/lippmann/compression_scratch/tests/scratch/lgnm1.txt");
    theCodec.compressTo(theOriginalFileNameAndPath, theCompressedFileNameAndPath);
    theCodec.decompressTo(theCompressedFileNameAndPath, theDecompressedFileNameAndPath);
    lg.close();
    bool passed = theCodec.theFilesAreEquivalent(theOriginalFileNameAndPath, theDecompressedFileNameAndPath);

    std::string passMessage;
    //std::cout << std::endl;
    if (passed)
        passMessage = "PASSED shortABC";
    else
        passMessage = "FAILED shortABC";
    std::cout << passMessage << std::endl;

    if (passed)
        return 0;
    else
        return 1;

}

int main()
{
    std::cout << std::endl;
    int numFailed = shortABC() +
    aaab() +
    quickishArith0() +
    quickishMDLPAR();

    if (numFailed == 0)
        std::cout << "PASSED all" << std::endl;
    else
        std::cout << "FAILED some" << std::endl;
}
