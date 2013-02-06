#include "domainModel/xArithCodec/xSymbolModel.hpp"

const int domainModel::xArithCodec::xSymbolModel::cumulativeCountLimit = 16384; //2^14 as per data compression book

domainModel::xArithCodec::xSymbolModel::xSymbolModel()
:
rawSymbolCounts(byteInspiredColumnVector::Zero()),
theRange(rangeVector::Zero()),
upToDate(false)
{

}

short int domainModel::xArithCodec::xSymbolModel::getScale()
{
    //if (!upToDate) rescaleModel();
    return (short int) theScale;
}

domainModel::xArithCodec::xRange
domainModel::xArithCodec::xSymbolModel::GetRange(int theSymbolValue)
{
    //if (!upToDate) rescaleModel();
    int theSymbolNumber = theSymbolValue;
    int theLow, theHigh;
    theLow = theRange(theSymbolNumber);
    theHigh = theRange(theSymbolNumber+1);

    //#ifdef COUTORLOG
    std:: cout << "arith high minus low: " << theHigh-theLow << std::endl;
    //#endif

    return domainModel::xArithCodec::xRange(theLow,theHigh,theScale);
}

int domainModel::xArithCodec::xSymbolModel::GetSymbolValue(int theRangePositionValue)
{
    //if (!upToDate) rescaleModel();
    int theRangePositionNumber = theRangePositionValue;
    int theSymbolNumber = -1;
    for (int i=0; i<theRange.size()-1; i++)
    {
        if ( (theRange(i) <= theRangePositionNumber) &&
            (theRangePositionNumber < theRange(i+1)) )
                {
                    theSymbolNumber = i;
                    break;
                }
    }
                assert(theSymbolNumber >= 0);
                assert(theSymbolNumber <= 255);
    return theSymbolNumber;
}

void domainModel::xArithCodec::xSymbolModel::addSymbol(domainModel::xMDLPAR::xSymbol theSymbol)
{
    //upToDate = false;
    rawSymbolCounts(theSymbol.getValue()) += 1;
}

void domainModel::xArithCodec::xSymbolModel::addSymbol(int theSymbolValue)
{
    //upToDate = false;
    rawSymbolCounts(theSymbolValue) += 1;
}

void domainModel::xArithCodec::xSymbolModel::scanSymbolsForInitialScaling(domainModel::xMDLPAR::xSymbolList theSymbolList)
{
    domainModel::xMDLPAR::xSymbol theCurrentSymbol;
    theSymbolList.moveToFirstSymbol(); //will never be empty?
    //int tempBob = 0;
    while(true)
    {
        theCurrentSymbol = theSymbolList.getCurrentSymbol();
        addSymbol(theCurrentSymbol.getValue());
        if (theSymbolList.atLastSymbol()) break;
        theSymbolList.moveToNextSymbol();
        //tempBob++;
    }

    double symbolCountLimit = 255;
    double maxSymbolCount = rawSymbolCounts.maxCoeff();
    double symbolScaleFactor = symbolCountLimit / maxSymbolCount;
    Eigen::Array<double,256,1> tempFloatingArray(rawSymbolCounts.cast<double>());
    tempFloatingArray *= symbolScaleFactor;
    rawSymbolCounts = tempFloatingArray.cast<int>();
    assert(rawSymbolCounts.maxCoeff() <= 255);
    assert(rawSymbolCounts.sum()>0);
    rescaleModel();

}

void domainModel::xArithCodec::xSymbolModel::rescaleAfterReloading()
{
    rescaleModel();
}

void domainModel::xArithCodec::xSymbolModel::setSymbolCount(int theSymbolValue, fileIndexType theSymbolCount)
{
    rawSymbolCounts(theSymbolValue) = theSymbolCount;
}

int domainModel::xArithCodec::xSymbolModel::getSymbolCount(int theSymbolValue)
{
    return rawSymbolCounts(theSymbolValue);
}

void domainModel::xArithCodec::xSymbolModel::rescaleModel()
{
    //A SLIGHT VARIANT OF THIS IS IN TWO PLACE AT ONCE MERGE!

    ///////////////////
    //very, very hasty way to try to bring down the symbol counts...
    //double symbolCountLimit = 255;//65535;
    //double maxSymbolCount = rawSymbolCounts.maxCoeff();
    //double symbolScaleFactor = symbolCountLimit / maxSymbolCount;
    //rawSymbolCounts *= symbolScaleFactor;
    ///////////////////

    double theTempCumulativeTotal = rawSymbolCounts.sum();
    double theScaleFactor = cumulativeCountLimit / theTempCumulativeTotal;
    byteInspiredDoubleColumnVector theDoubleRoughScaledRange = rawSymbolCounts.cast<double>() * theScaleFactor;
    byteInspiredColumnVector theRoughScaledRange = theDoubleRoughScaledRange.cast<int>();
    byteInspiredColumnVector theNonZeroRange;
    for (int i = magicNumberMinByteIndex; i <= magicNumberMaxByteIndex; i++)
    {
        if (theRoughScaledRange(i) < 1)
            theNonZeroRange(i) = 1;
        else
            theNonZeroRange(i) = theRoughScaledRange(i);
    }
    double theCurrentTotal = theNonZeroRange.sum();

    //sort
      typedef int Index; typedef double Scalar;
      std::vector< std::pair<Scalar, Index> > ultimatelySortedStdVector;
      ultimatelySortedStdVector.reserve(magicNumberNumStatesOfAByte);

      for (int i=0; i<magicNumberNumStatesOfAByte; i++)
        ultimatelySortedStdVector.push_back( std::make_pair<Scalar,Index>(theNonZeroRange(i),i) );
      std::sort(ultimatelySortedStdVector.begin(),
                ultimatelySortedStdVector.end()); //sort ascending
      while (theCurrentTotal >= cumulativeCountLimit)
      {
        for (int i=magicNumberNumStatesOfAByte-1; i>=0; i--) //go descending
        {
          if (theCurrentTotal < cumulativeCountLimit) break;
          if ( theNonZeroRange(ultimatelySortedStdVector[i].second) >= 2)
          {
            theNonZeroRange(ultimatelySortedStdVector[i].second) -= 1;
            theCurrentTotal -= 1;
          }
        }
      }

      theRange(0) = 0;
      for (int i=magicNumberMinByteIndex; i<= magicNumberMaxByteIndex; i++)
        theRange(i+1) = theRange(i) + theNonZeroRange(i);

      theScale = theRange.maxCoeff();
      //assert(rawSymbolCounts.maxCoeff() < 255); //i do nothing to actually guarantee this above
      assert(theScale<=cumulativeCountLimit);

}
