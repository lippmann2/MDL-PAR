#include "domainModel/xMDLPAR/xPredictor.hpp"

domainModel::xMDLPAR::xPredictionComponents
domainModel::xMDLPAR::xPredictor::getPredictionComponents(
    domainModel::xMDLPAR::xSymbolList theCausalSymbols,
    domainModel::xMDLPAR::xContext theSymbolContext,
    domainModel::xMDLPAR::xContextRepository* theContextRepository)
{

    domainModel::xMDLPAR::xPredictionComponents thePredictionComponents;

    //domainModel::xMDLPAR::xContextList
    //    theContextList =
    //        domainModel::xMDLPAR::xPredictor::getSimilarContexts(
    //            theCausalSymbols, theSymbolContext);

    if (!theSymbolContext.isComplete())
    {
        thePredictionComponents.meaningfulPrediction = false;
        return thePredictionComponents;
    }

    domainModel::xMDLPAR::xContextList
        theContextList =
            theContextRepository->addContextAndGetSimilarContexts(theSymbolContext);

    if (theContextList.numContexts() < 2) //<2 <=3
    {
        thePredictionComponents.meaningfulPrediction = false;
        return thePredictionComponents;
    }

    domainModel::xMDLPAR::xPositionRanking thePositionRanking(
        domainModel::xMDLPAR::xConverter::toPositionRanking(theContextList));

    fileIndexType maxK = std::min(theContextList.numContexts()-1,G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES); //to prevent underdetermined system //thePositionRanking.numPositions();

    if (maxK == 0)
    {
        thePredictionComponents.meaningfulPrediction = false;
        return thePredictionComponents;
    }

    std::vector<double> L; L.reserve(maxK);
    std::vector<domainModel::xMDLPAR::xErrorDistribution> theErrorDistributions; theErrorDistributions.reserve(maxK);
    std::vector<domainModel::xMDLPAR::xFilterCoefficients> allFilterCoefficients; allFilterCoefficients.reserve(maxK);
    std::vector<domainModel::xMDLPAR::xSupportMask> theSupportMasks; theSupportMasks.reserve(maxK);
    std::vector<domainModel::xMDLPAR::xTrainingSet> theTrainingSets; theTrainingSets.reserve(maxK);
    domainModel::xMDLPAR::xTrainingSet candidateTrainingSet;
    domainModel::xMDLPAR::xSupportMask candidateSupportMask;
    double theStd, H, S;
    thePredictionComponents.meaningfulPrediction = false;
    fileIndexType kUsed=0;
    for (fileIndexType k = 2; k <= maxK; k++) //stat k at 2, put in k-1 below? the number of unknowns for controlling rank...
    {
        //the push_back k-1's are different than this k-1:

        xSupportMask candidateSupportMask(thePositionRanking,k-1);
        xTrainingSet candidateTrainingSet(domainModel::xMDLPAR::xConverter::toTrainingSet(theContextList,
                                                                                          candidateSupportMask,
                                                                                          theSymbolContext));

        if (!candidateTrainingSet.overdetermined) continue;

        thePredictionComponents.meaningfulPrediction = true;
        kUsed++;

        theSupportMasks.push_back(candidateSupportMask);
        theTrainingSets.push_back(candidateTrainingSet);

        allFilterCoefficients.push_back(
            domainModel::xMDLPAR::xConverter::toFilterCoefficients(theTrainingSets.back(),k));

        //if (allFilterCoefficients.back().rank >=k )
        //{
        //    L.push_back(std::numeric_limits<double>::infinity());
        //    theErrorDistributions.push_back(xErrorDistribution());
        //    continue;
        //}

        //thePredictionComponents.meaningfulPrediction = true;
        //kUsed++;

        //    && allFilterCoefficients[k-1].rank < k) //>= //3
        //{
        //    thePredictionComponents.meaningfulPrediction = true;
        //    kUsed++;
        //}
        //else
        //{
        //    break;
        //    //L.push_back(std::numeric_limits<double>::infinity());
        //    //allFilterCoefficients.push_back(xFilterCoefficients()); //junk
        //    //theErrorDistributions.push_back(xErrorDistribution()); //junk
        //    //continue;
        //}

        //allFilterCoefficients.push_back(
        //    domainModel::xMDLPAR::xConverter::toFilterCoefficients(theTrainingSets[k-1]));

        theStd = domainModel::xMDLPAR::xPredictor::getStd(theTrainingSets.back(),
                                                                 allFilterCoefficients.back());

        //std::cout << "std: " << theStd << std::endl;

        int debugTemp;
        if (theStd>0)
        {
            debugTemp = 1;
            debugTemp = 2;
        }

        theErrorDistributions.push_back(xErrorDistribution(theStd));

        H = domainModel::xMDLPAR::xPredictor::getH(theErrorDistributions.back());

        //assert(H != -0);
        if (H==-0)
        {
            int testbob = 1;
            int testbob2 = 1;
        }

        S = theTrainingSets.back().supports->rows();

        L.push_back( H + ( (k * std::log(S)) / (std::log(2)*2*S) ) );

        //std::cout << "h: " << H << " s: " << S << " k: " << k << std::endl;

    }
    if (thePredictionComponents.meaningfulPrediction == false) //didn't get a useful training set despite getting enough contexts
        return thePredictionComponents;

    //get index of smallest L
    double minKidx, minL;
    minL = std::numeric_limits<double>::infinity();
    //for (fileIndexType i=0; i < maxK; i++)
    for (fileIndexType i=0; i<kUsed; i++)
        if (L[i] < minL) {minL = L[i]; minKidx = i;}

    thePredictionComponents.meaningfulPrediction = true;
    thePredictionComponents.theErrorDistribution = theErrorDistributions[minKidx];
    thePredictionComponents.theSupportMask = theSupportMasks[minKidx];
    thePredictionComponents.theFilterCoefficients = allFilterCoefficients[minKidx];

    //std::cout << "std: " << thePredictionComponents.theErrorDistribution.theStandardDeviation << std::endl;

    int tempdebugg;
    if (minKidx > 0)
    {
        tempdebugg = 1;
        tempdebugg = tempdebugg - 3;
    }

    #ifdef COUTORLOG
    lg << "Training Set: " << std::endl;
    lg << *(theTrainingSets[minKidx].rawSupportIndices) << std::endl;
    #endif

    return thePredictionComponents;
}

double
domainModel::xMDLPAR::xPredictor::getH(domainModel::xMDLPAR::xErrorDistribution theErrorDistribution)
{
    double accumulator = 0;
    double pd;
    for (int i=G_MAGIC_NUMBER_MIN_PREDICTION_ERROR;
        i<=G_MAGIC_NUMBER_MAX_PREDICTION_ERROR; i++)
    {
        pd = theErrorDistribution.Pd(i);
        if (pd==0) continue;
        accumulator += pd * std::log(pd) / std::log(2);
    }
    return -accumulator;
}

double
domainModel::xMDLPAR::xPredictor::getStd(
    domainModel::xMDLPAR::xTrainingSet theTrainingSet,
    domainModel::xMDLPAR::xFilterCoefficients theFilterCoefficients)
{
    double numSupports = theTrainingSet.supports->rows();
    assert(numSupports>0);
    if (numSupports == 1) return 0;
    arrayType tempArray(theTrainingSet.supports->cols());
    arrayType tempResults(numSupports);
    for (fileIndexType i = 0; i<numSupports; i++)
    {
        //tempArray =
        //    theTrainingSet.supports->col(i).array() * ////////
        //        theFilterCoefficients.filterCoefficients->array();
        tempArray =
            theTrainingSet.supports->row(i) *
                *theFilterCoefficients.filterCoefficients;
        tempResults(i) = tempArray.sum();

        assert(theFilterCoefficients.filterCoefficients->sum() == theFilterCoefficients.filterCoefficients->sum());
        assert(tempArray.sum() == tempArray.sum());

    }

    //std::cout << "<<<<<<<<<<<<<<<<<<<"<< std::endl;

    //std::cout << "tr: " << tempResults << std::endl;

    //tempResults -= theTrainingSet.values->array();

    //std::cout << "tr-: " << tempResults << std::endl;

    //double theMean = tempResults.mean();
    //if (theTrainingSet.supports->rows() > 4 && theTrainingSet.supports->cols()>3)
    //{
    //    std::cout << "trainingset num cols: " << theTrainingSet.supports->cols() << std::endl; //debug
    //}
    //std::cout << "trainingset supports: " << *theTrainingSet.supports << std::endl;
    //std::cout << "trainingset values: " << *theTrainingSet.values << std::endl;
    //std::cout << "tempresults: " << tempResults << std::endl;

    tempResults -= theTrainingSet.values->array();
    double theMean = tempResults.mean();
    //std::cout << "trdiff: " << tempResults << std::endl;
    //std::cout << "filtercoeffs: " << *theFilterCoefficients.filterCoefficients << std::endl;
    tempResults -= theMean;
    //std::cout << "tempresults - mean: " << tempResults << std::endl;
    tempResults = tempResults.square();
    //std::cout << "and now squared: " << tempResults << std::endl;
    double tempAlmostDone = tempResults.sum();
    //double tempAlmostDone = tempResults.matrix().norm();
    tempAlmostDone /= (numSupports - 1); //(numSupports - 1);
    //if (tempAlmostDone < 0) return 0; //saying it's basically zero so no nan.
    double theStd = std::sqrt(tempAlmostDone);
    //std::cout << "sl: " << theTrainingSet.supports->cols() << std::endl;
    //std::cout << "std: " << theStd << std::endl;
    assert(theStd==theStd); //!nan
    return theStd;
}

int
domainModel::xMDLPAR::xPredictor::getError(
    domainModel::xMDLPAR::xSupportMask theSupportMask,
    domainModel::xMDLPAR::xFilterCoefficients theFilterCoefficients,
    domainModel::xMDLPAR::xContext theContext,
    domainModel::xMDLPAR::xSymbol theSymbol)
{

    int thePrediction = applyFilter(theFilterCoefficients,
                                    theContext,
                                    theSupportMask);

    int theActualSymbolValue =
        domainModel::xMDLPAR::xConverter::toValue(theSymbol);

    assert(domainModel::xMDLPAR::xConverter::toValue(theSymbol) ==
           domainModel::xMDLPAR::xConverter::toAdjacentSymbolValue(theContext));

    int thePredictionError = theActualSymbolValue - thePrediction;

    assert(thePredictionError >= -255 && thePredictionError <= 255);

    //clip? nuke if wayyyyyy too off? just clipping for now... ok if clip when decoding too, right?
    //do this in apply filter because it's used by both...
    //if (thePredictionError < -255)
    //    thePredictionError  = -255;
    //if (thePredictionError > 255)
    //    thePredictionError = 255;

    //assert(thePredictionError >= -255); //magic number bad to leave it here
    //assert(thePredictionError <= 255);

    #ifdef COUTORLOG
    std::cout << "the prediction error: " << thePredictionError << std::endl;
    #endif

    return thePredictionError;
}

int
domainModel::xMDLPAR::xPredictor::applyFilter(
    domainModel::xMDLPAR::xFilterCoefficients theFilterCoefficients,
    domainModel::xMDLPAR::xContext theContext,
    domainModel::xMDLPAR::xSupportMask theSupportMask)
{

    rowVectorType_ptr theSupport(
        domainModel::xMDLPAR::xConverter::toSupport(theSupportMask,
                                                    theContext));

    rowVectorType_ptr theSupportIndices(
        domainModel::xMDLPAR::xConverter::toRawSupportIndices(theSupportMask,
                                                              theContext));
    #ifdef COUTORLOG
    lg << "support indices: " << std::endl << *theSupportIndices << std::endl;
    #endif

    arrayType tempArray(theSupport->size());

    //std::cout << theFilterCoefficients.filterCoefficients->array() << std::endl;

    //tempArray = theSupport-> * theFilterCoefficients.filterCoefficients->transpose();
    //assert( tempArray.rows() == 1);

    //double tempPrediction = tempArray.sum();

    double tempPrediction = theSupport->dot(*theFilterCoefficients.filterCoefficients);



    int quantizedPrediction = int(std::floor(tempPrediction+0.5)); //is this the best place to round?

    //clipping... better than aborting a meaningful prediction?
    if (quantizedPrediction < 0)
        quantizedPrediction = 0;
    if (quantizedPrediction > 255)
        quantizedPrediction = 255;

    //assert should be positive or zero, yes?

    return quantizedPrediction;
}

/*domainModel::xMDLPAR::xContextList
domainModel::xMDLPAR::xPredictor::getSimilarContexts(
    domainModel::xMDLPAR::xSymbolList theSymbolList,
    domainModel::xMDLPAR::xContext theComparisonContext)
{
    domainModel::xMDLPAR::xContextList theContextList;
    if (theSymbolList.isEmpty()) return theContextList;

    theSymbolList.moveToFirstSymbol();

    domainModel::xMDLPAR::xSymbol theCurrentSymbol;
    domainModel::xMDLPAR::xContext theCurrentContext;
    while(true)
    {
        theCurrentSymbol = theSymbolList.getCurrentSymbol();
        theCurrentContext = domainModel::xMDLPAR::xConverter::toCausalAdjacentContext(theCurrentSymbol);
        if ( domainModel::xMDLPAR::xPredictor::theContextsAreSimilarEnough(theCurrentContext,theComparisonContext) )
            theContextList.addContext(theCurrentContext);

        if (theSymbolList.atLastSymbol()) break;
        theSymbolList.moveToNextSymbol();
    }
    return theContextList;
}*/

/*bool
domainModel::xMDLPAR::xPredictor::theContextsAreSimilarEnough(
    const domainModel::xMDLPAR::xContext& a,
    const domainModel::xMDLPAR::xContext& b)
{

    if ( !(a.isComplete()) || !(b.isComplete()) )
        return false;

    //is it dealing automatically with the fact that these are pointers?
    symbolsAsValues aValues = domainModel::xMDLPAR::xConverter::toValues(a);
    symbolsAsValues bValues = domainModel::xMDLPAR::xConverter::toValues(b);

    //euclidean distance between the two contexts
    Eigen::VectorXd tempValues;//(G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES);
    tempValues = *aValues - *bValues;
    //tempValues = tempValues.array().square(); //assert or unit test that this actually works
    //tempValues = tempValues.square();
    double theRawDistance = tempValues.norm();

    double theNormalizedSimilarity = 1- (theRawDistance/G_MAGIC_NUMBER_MAX_RAW_CONTEXT_DISTANCE);
    bool similarEnough;
    if (theNormalizedSimilarity >=
            G_MAGIC_NUMBER_NORMALIZED_CONTEXT_SIMILARITY_THRESHOLD)
                similarEnough = true;
            else
                similarEnough = false;

    //if (similarEnough)
        std::cout << "se: " << theNormalizedSimilarity << std::endl;

    return similarEnough;
}*/

bool
domainModel::xMDLPAR::xPredictor::theSupportsAreSimilarEnough(
    rowVectorType_ptr a, rowVectorType_ptr b)
{

    vectorType tempValues = *a - *b;
    //tempValues.array().square();
    double theRawDistance = tempValues.norm();

    double maxRawSupportDistance =
        std::sqrt(tempValues.size() * std::pow(G_MAGIC_NUMBER_MAX_SYMBOL_VALUE,2));
    double theNormalizedSimilarity = 1 - (theRawDistance/maxRawSupportDistance);

    bool similarEnough;
    if (theNormalizedSimilarity >=
            G_MAGIC_NUMBER_NORMALIZED_SUPPORT_SIMILARITY_THRESHOLD)
                similarEnough = true;
            else
                similarEnough = false;

    return similarEnough;

}
