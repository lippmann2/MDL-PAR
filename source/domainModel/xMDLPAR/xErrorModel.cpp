#include "domainModel/xMDLPAR/xErrorModel.hpp"

//domainModel::xMDLPAR::xModel::initializeWordyConstants();

const int domainModel::xMDLPAR::xErrorModel::highestCumulativeCount = 16384; //2^14

domainModel::xMDLPAR::xErrorModel::xErrorModel() {}

domainModel::xMDLPAR::xErrorModel::xErrorModel(domainModel::xMDLPAR::xErrorDistribution theDistribution)
{

    byteInspiredDoubleColumnVector firstPassRange;
  for (discreteNumberOfIncidentalType domainIndex = 0; domainIndex < magicNumberSizeOfErrorRange; domainIndex++)
  {
      int pDIndex = magicNumberMinPredictionError + domainIndex;
    //does it matter what order the i's are in or not????
    //does it matter whether the errors are signed or anything or not????
    //does the shape of the pdf/cdf matter for my purposes???
    //does it have to be "continuous"???
    firstPassRange(domainIndex) = theDistribution.Pd(pDIndex);
  }

  //A SLIGHT VARIANT OF THIS IS IN TWO PLACES AT ONCE MERGE!??

  /////////////////
  //very, very hasty way to try to bring down the symbol counts...
  //double symbolCountLimit = 65535;
  //double maxSymbolCount = firstPassRange.maxCoeff();
  //double symbolScaleFactor = symbolCountLimit / maxSymbolCount;
  //firstPassRange *= symbolScaleFactor;
  /////////////////


  double theTempCumulativeTotal = firstPassRange.sum();
  double theScaleFactor = highestCumulativeCount / theTempCumulativeTotal;

  byteInspiredDoubleColumnVector tempVector = firstPassRange * theScaleFactor;
  byteInspiredColumnVector theRoughScaledRange = tempVector.cast<int>(); //element-wise multiplication

  byteInspiredColumnVector theNonZeroRange;
  //theNonZeroRange = (theRoughScaledRange == 0).select(allOnes,theRoughScaledRange);
  //so i desperately wish that I could vectorize this somehow (if such a thing actually exists in real life
    // perhaps a maximum compiler optimization will unroll this loop?
    if (theRoughScaledRange.minCoeff() < 1)
    {
        for (discreteNumberOfIncidentalType i = 0; i < magicNumberSizeOfErrorRange; i++)
        {
            if (theRoughScaledRange(i) < 1)
                theNonZeroRange(i) = 1;
            else
                theNonZeroRange(i) = theRoughScaledRange(i);
        }
    }
    else
        theNonZeroRange = theRoughScaledRange;

  double theCurrentTotal = theNonZeroRange.sum(); //temp

  //sort
  typedef discreteNumberOfIncidentalType Index; typedef double Scalar;
  std::vector< std::pair<Scalar, Index> > ultimatelySortedStdVector;
  ultimatelySortedStdVector.reserve(magicNumberSizeOfErrorRange);

  for (discreteNumberOfIncidentalType i=0; i<magicNumberSizeOfErrorRange; i++)
    ultimatelySortedStdVector.push_back( std::make_pair<Scalar,Index>(theNonZeroRange(i),i) );
  std::sort(ultimatelySortedStdVector.begin(), ultimatelySortedStdVector.end() );
  while (true)
  {
    for (int i=0; i<magicNumberSizeOfErrorRange; i++) //make the smallest stuff even smaller if safe to do so
    {
      if (theCurrentTotal < highestCumulativeCount) break;
      if ( theNonZeroRange(ultimatelySortedStdVector[i].second) >= 2)
      {
	theNonZeroRange(ultimatelySortedStdVector[i].second) -= 1;
	theCurrentTotal -= 1;
      }
    }
    if (theCurrentTotal < highestCumulativeCount) break;
  }

  theRange(0) = 0;
  for (discreteNumberOfIncidentalType i=0; i< magicNumberSizeOfErrorRange; i++)
    theRange(i+1) = theRange(i) + theNonZeroRange(i);

  theScale = theRange.maxCoeff();

  assert(theScale <= highestCumulativeCount);

}

short int domainModel::xMDLPAR::xErrorModel::getScale()
{
    return (short int) theScale;
}

domainModel::xArithCodec::xRange domainModel::xMDLPAR::xErrorModel::GetRange(int theSymbolValue)
{
  int theSymbolNumber = theSymbolValue;//domainModel::xMDLPAR::xConverter::toValue(theSymbol);
  assert(theSymbolNumber >= magicNumberMinPredictionError);
  assert(theSymbolNumber <= magicNumberMaxPredictionError);

    int tempdebug;
    if (theSymbolNumber == 0)
    {
        tempdebug  =1;
    }

  int theSymbolIndex = theSymbolNumber - magicNumberMinPredictionError;
  assert(theSymbolIndex >= 0);
  assert(theSymbolIndex < magicNumberSizeOfErrorRange);

  discreteNumberOfIncidentalType theLow, theHigh;
  theLow = theRange(theSymbolIndex);
  theHigh = theRange(theSymbolIndex+1);

  //debug
  //#ifdef COUTORLOG
  //int tempme;
  std::cout << "high minus low: " << theHigh - theLow << std::endl;
  //if (theHigh - theLow > 1)
  //{
  //    tempme = 1;
  //}
  //end debug
  //#endif

  return domainModel::xArithCodec::xRange(theLow, theHigh, theScale);
}

int domainModel::xMDLPAR::xErrorModel::GetSymbolValue(int theRangePositionValue)
{
  //discreteNumberOfIncidentalType theRangePositionNumber = theRangePosition.getRangePositionAsInt();
  int theRangePositionNumber = theRangePositionValue;
  int theErrorIndex = magicNumberMinPredictionError-1; //init to meaningless value
  for (discreteNumberOfIncidentalType i=0; i<theRange.size()-1; i++)
  {
    if ( (theRange(i) <= theRangePositionNumber) &&
        (theRangePositionNumber < theRange(i+1)) )
        {
            theErrorIndex = i;
            break;
        }
  }

  int theErrorNumber = theErrorIndex + magicNumberMinPredictionError;

  assert(theErrorNumber>= magicNumberMinPredictionError);
  assert(theErrorNumber<=magicNumberMaxPredictionError);

  return theErrorNumber;
}

//domainModel::xMDLPAR::xErrorModel::~xErrorModel() {}

//void domainModel::xMDLPAR::xErrorModel::initializeWordyConstants()
//{

    /*domainModel::xMDLPAR::xErrorModel::byteInspiredColumnVector domainModel::xMDLPAR::xErrorModel::theSymbols(256,1);
    domainModel::xMDLPAR::xErrorModel::theSymbols <<
    0,   1,   2,   3,   4,   5,   6,   7,   8,   9,
    10,  11,  12,  13,  14,  15,  16,  17,  18,  19,
    20,  21,  22,  23,  24,  25,  26,  27,  28,  29,
    30,  31,  32,  33,  34,  35,  36,  37,  38,  39,
    40,  41,  42,  43,  44,  45,  46,  47,  48,  49,
    50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
    60,  61,  62,  63,  64,  65,  66,  67,  68,  69,
    70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
    80,  81,  82,  83,  84,  85,  86,  87,  88,  89,
    90,  91,  92,  93,  94,  95,  96,  97,  98,  99,
    100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
    110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
    120, 121, 122, 123, 124, 125, 126, 127, 128, 129,
    130, 131, 132, 133, 134, 135, 136, 137, 138, 139,
    140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
    150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
    160, 161, 162, 163, 164, 165, 166, 167, 168, 169,
    170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
    180, 181, 182, 183, 184, 185, 186, 187, 188, 189,
    190, 191, 192, 193, 194, 195, 196, 197, 198, 199,
    200, 201, 202, 203, 204, 205, 206, 207, 208, 209,
    210, 211, 212, 213, 214, 215, 216, 217, 218, 219,
    220, 221, 222, 223, 224, 225, 226, 227, 228, 229,
    230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
    240, 241, 242, 243, 244, 245, 246, 247, 248, 249,
    250, 251, 252, 253, 254, 255;*/

    //domainModel::xMDLPAR::xErrorModel::byteInspiredColumnVector domainModel::xMDLPAR::xErrorModel::allOnes::Constant(256,1,1) // <<
    /*1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1,1,1,1,1,1,
    1,1,1,1,1;*/
//}
