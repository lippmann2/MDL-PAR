#include "domainModel/xMDLPAR/xConverter.hpp"

//domainModel::xMDLPAR::xConverter::symbolAsValue
symbolAsValue
domainModel::xMDLPAR::xConverter::toValue(const xSymbol& theSymbol) //, const xCodecBuffer& theCodecBuffer)
{
    int tempInt = theSymbol.codecBuffer_ptr->getByteAsInt(theSymbol.byteIndex);
    return tempInt;
}

//domainModel::xMDLPAR::xSymbolList
//domainModel::xMDLPAR::xConverter::toSymbolList(
//    boost::shared_ptr<domainModel::xMDLPAR::xCodecBuffer> theCodecBuffer_ptr)
domainModel::xMDLPAR::xSymbolList
domainModel::xMDLPAR::xConverter::toSymbolList(
    domainModel::xMDLPAR::xCodecBuffer* theCodecBuffer_ptr)
{
    fileIndexType theLow = 0;
    fileIndexType theHigh;
    fileIndexType numBytesCurrentlyInBuffer = theCodecBuffer_ptr->numBytesCurrentlyInBuffer();
    domainModel::xMDLPAR::xSymbolList theSymbolList;
    if (numBytesCurrentlyInBuffer != 0)
    {
        theHigh = theCodecBuffer_ptr->numBytesCurrentlyInBuffer()-1;
        theSymbolList = domainModel::xMDLPAR::xSymbolList(theLow, theHigh, theCodecBuffer_ptr);
        theSymbolList.nonEmptyList = true;
    }
    else
    {
        theHigh = -1;
        theSymbolList = domainModel::xMDLPAR::xSymbolList(theLow,theHigh,theCodecBuffer_ptr);
        theSymbolList.nonEmptyList = false;
    }

    return theSymbolList;
}

domainModel::xMDLPAR::xSymbolList
domainModel::xMDLPAR::xConverter::toCausalSymbols(const xSymbol& theSymbol)
{
    fileIndexType theLow = 0;
    fileIndexType theHigh;
    //fileIndexType theHigh = theSymbol.byteIndex - 1;
    if (theSymbol.byteIndex == 0)
        theHigh = 0;
    else
        theHigh = theSymbol.byteIndex - 1;
    domainModel::xMDLPAR::xSymbolList theSymbolList(theLow, theHigh, theSymbol.codecBuffer_ptr);
    return theSymbolList;
}

domainModel::xMDLPAR::xContext
domainModel::xMDLPAR::xConverter::toCausalAdjacentContext(const xSymbol& theSymbol)
{
    domainModel::xMDLPAR::xContext theContext(
        theSymbol.byteIndex - G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES,
        theSymbol.codecBuffer_ptr);//domainModel::xMDLPAR::xContext::magicNumberContextSizeInBytes);
    if (theSymbol.byteIndex < G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES)
        theContext.isCompleteContext = false; //needed because of unsigned wraparound
    else
        theContext.isCompleteContext = true;

    //assert( (theContext.contextStartIndex < (fileIndexType)0-G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES) &&
    //theContext.isCompleteContext == true);

    //assert(theSymbol.byteIndex < G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES && !theContext.isCompleteContext

    return theContext;
}

domainModel::xMDLPAR::xContext
domainModel::xMDLPAR::xConverter::toHeadContext(const xSymbolList& theSymbolList)
{
    domainModel::xMDLPAR::xContext theHeadContext(
        theSymbolList.highIndex - G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES+1,
        theSymbolList.codecBuffer_ptr);
    if (theSymbolList.highIndex < G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES-1)
        theHeadContext.isCompleteContext = false; //needed because of unsigned wraparound
    else
        theHeadContext.isCompleteContext = true;
    if (theSymbolList.isEmpty()) theHeadContext.isCompleteContext = false;
    return theHeadContext;
}

symbolsAsValues
domainModel::xMDLPAR::xConverter::toValues(const xContext& theContext)
{
    //SHOULD ERROR OUT IF NOT A COMPLETE CONTEXT!!!
    //as in, it doesn't, but it should

    symbolsAsValues theSymbolsAsValues(
        new Eigen::Map<Eigen::VectorXd>(
            &(theContext.codecBuffer_ptr->theByteBuffer[theContext.contextStartIndex]),
            G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES-1,1));

    return theSymbolsAsValues;
}

int
domainModel::xMDLPAR::xConverter::toAdjacentSymbolValue(
    domainModel::xMDLPAR::xContext theContext)
{
    fileIndexType theSymbolValueIndex =
        theContext.contextStartIndex +
            G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES; //-1 dnow;
    int theSymbolValue = theContext.codecBuffer_ptr->getByteAsInt(theSymbolValueIndex);
    //std::cout << theSymbolValue << std::endl;
        return theSymbolValue;
}

Eigen::Array<double,Eigen::Dynamic,1>
domainModel::xMDLPAR::xConverter::toAdjacentSymbolValues(
    domainModel::xMDLPAR::xContextList theContextList)
{

    //NRVO, I hope? Won't trigger a big copy?
    //Otherwise, pass back a pointer to an Eigen::Array
    Eigen::Array<double,Eigen::Dynamic,1> theSymbolValues(theContextList.numContexts(),1);

    for (fileIndexType i = 0; i<theContextList.numContexts(); i++)
    {

        fileIndexType theSymbolValueIndex =
            theContextList.theContexts.at(i).contextStartIndex +
                G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES; //- 1 dnow;
        assert(theSymbolValueIndex < theContextList.theContexts.at(i).codecBuffer_ptr->theByteBuffer.size());
        theSymbolValues(i) = theContextList.theContexts.at(i).codecBuffer_ptr->getByteAsInt(theSymbolValueIndex);
    }
    return theSymbolValues;
}

Eigen::Array<double,Eigen::Dynamic,1>
domainModel::xMDLPAR::xConverter::toSymbolValuesAtIndex(
    fileIndexType theIndex,
    domainModel::xMDLPAR::xContextList theContextList)
{
    //NRVO, I hope? Won't trigger a big copy?
    //Otherwise, pass back a pointer to an Eigen::Array
    Eigen::Array<double,Eigen::Dynamic,1> theSymbolValues(theContextList.numContexts(),1);

    for (fileIndexType i = 0; i<theContextList.numContexts(); i++)
    {
        fileIndexType theSymbolValueIndex =
            theContextList.theContexts.at(i).contextStartIndex +
                theIndex;
        theSymbolValues(i) = theContextList.theContexts.at(i).codecBuffer_ptr->getByteAsInt(theSymbolValueIndex);
    }
    return theSymbolValues;
}

domainModel::xMDLPAR::xPositionRanking
domainModel::xMDLPAR::xConverter::toPositionRanking(domainModel::xMDLPAR::xContextList theContextList)
{
    ///////////////
    Eigen::Array<double,Eigen::Dynamic,1> adjacentSymbolValues(
        domainModel::xMDLPAR::xConverter::toAdjacentSymbolValues(theContextList));

    double numContexts = theContextList.numContexts();

    std::vector< std::pair<double,fileIndexType> > correlationIndexPairs;
    correlationIndexPairs.reserve(G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES);

    for (fileIndexType i = 0; i< G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES; i++)
    {

        Eigen::Array<double,Eigen::Dynamic,1> symbolValuesAtIndex(
            domainModel::xMDLPAR::xConverter::toSymbolValuesAtIndex(i, theContextList));

        assert(adjacentSymbolValues.size() == symbolValuesAtIndex.size());

        //all these operations are coefficient-wise



        Eigen::Array<double,Eigen::Dynamic,1> temp(symbolValuesAtIndex * adjacentSymbolValues);
        double A = numContexts * temp.sum();

        double B = adjacentSymbolValues.sum() * symbolValuesAtIndex.sum();

        Eigen::Array<double,Eigen::Dynamic,1> temp2(adjacentSymbolValues.square());
        double C = std::sqrt(numContexts*temp2.sum() - std::pow(adjacentSymbolValues.sum(),2));

        Eigen::Array<double,Eigen::Dynamic,1> temp3(symbolValuesAtIndex.square());
        double D = std::sqrt(numContexts*temp3.sum() - std::pow(symbolValuesAtIndex.sum(),2));

        //eqn 7 in paper:
        //correlationsIndexedByPositionWithinContext(i) = (A - B) / (C * D);
        double correlationCoeff;
        if (std::abs(A-B) < 0.000000000000001)
            correlationCoeff = 0;
        else
            correlationCoeff = (A - B) / (C * D);

        assert(correlationCoeff <= 1.1 && correlationCoeff >= -1.1);

        //making a call here to do abs, this is late in the game, will everything else still work?
        correlationIndexPairs.push_back( std::make_pair<double,fileIndexType>(std::abs(correlationCoeff),i) );
    }

    std::sort(correlationIndexPairs.begin(), correlationIndexPairs.end() );

    //hopefully this copy will be elided...
    //boost::shared_ptr<Eigen::Array<fileIndexType,Eigen::Dynamic,1,0,G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES,1> >
    //    indicesDescentSortedByCorrelation(new
    //        Eigen::Array<fileIndexType,Eigen::Dynamic,1,0,G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES,1>);
    boost::shared_ptr<Eigen::Array<fileIndexType,Eigen::Dynamic,1> >
        indicesDescentSortedByCorrelation(new
            Eigen::Array<fileIndexType,Eigen::Dynamic,1>(G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES)); //bob

    //bring back only indices only up to those that still have positive correlations
    //for (fileIndexType i = 0; correlationIndexPairs[i].first > 0; i++)
    //    indicesDescentSortedByCorrelation->coeffRef(i) = correlationIndexPairs[i].second;
    //part of the whole abs thing:
    for (fileIndexType i = 0; i < correlationIndexPairs.size(); i++)
        indicesDescentSortedByCorrelation->coeffRef(i) = correlationIndexPairs[i].second;

    //std::cout << "corr sort: " << *indicesDescentSortedByCorrelation << std::endl;

    domainModel::xMDLPAR::xPositionRanking thePositionRanking;
    thePositionRanking.theIndices_ptr = indicesDescentSortedByCorrelation;
    return thePositionRanking;

    //////////////
}

domainModel::xMDLPAR::xTrainingSet
domainModel::xMDLPAR::xConverter::toTrainingSet(
    domainModel::xMDLPAR::xContextList theContextList,
    domainModel::xMDLPAR::xSupportMask theSupportMask,
    domainModel::xMDLPAR::xContext thePredictionContext)
{
    domainModel::xMDLPAR::xTrainingSet theTrainingSet;

    rowVectorType_ptr predictionSupport(toSupport(theSupportMask, thePredictionContext));
    fileIndexType n = predictionSupport->size();

    vectorType_ptr values(new vectorType(theContextList.numContexts()));
    matrixType_ptr supports(new matrixType(theContextList.numContexts(),n));
    matrixType_ptr rawSupportIndices(new matrixType(theContextList.numContexts(),n));

    domainModel::xMDLPAR::xContext currentContext;
    theContextList.moveToFirstContext();
    fileIndexType supportRowIndex = 0;
    while(true)
    {

        currentContext = theContextList.getCurrentContext();
        rowVectorType_ptr candidateSupport(toSupport(theSupportMask,currentContext));
        rowVectorType_ptr candidateRawSupportIndices(toRawSupportIndices(theSupportMask,currentContext));

        if (domainModel::xMDLPAR::xPredictor::theSupportsAreSimilarEnough(
            predictionSupport,candidateSupport))
        {

            supports->block(supportRowIndex,0,1,n) =
                candidateSupport->head(n);

            values->coeffRef(supportRowIndex) =
                domainModel::xMDLPAR::xConverter::toAdjacentSymbolValue(currentContext);

            rawSupportIndices->block(supportRowIndex,0,1,n) =
                candidateRawSupportIndices->head(n);

            supportRowIndex +=1;

        }

        if (theContextList.atLastContext()) break;
        theContextList.moveToNextContext();
        //supportRowIndex += 1;
    }

    matrixType_ptr theUsedSupports(new matrixType(supports->block(0,0,supportRowIndex,n)));
    theTrainingSet.supports = theUsedSupports;

    vectorType_ptr theUsedValues(new vectorType(values->head(supportRowIndex)));
    theTrainingSet.values = theUsedValues;

    matrixType_ptr theUsedRawSupportIndices(new matrixType(rawSupportIndices->block(0,0,supportRowIndex,n)));
    theTrainingSet.rawSupportIndices = theUsedRawSupportIndices;

    //std::cout << "used supports: " << std::endl << *theUsedSupports << std::endl;
    //std::cout << "used values: " << std::endl << *theUsedValues << std::endl;

    theTrainingSet.theSize = supportRowIndex;

    ////////////
    //http://www.physicsforums.com/showthread.php?t=420317
    //Let A be tha matrix of coefficients and N be the vector of inhomogeneous terms, and let (A|N) the matrix obtained by putting A and N in a same matrix. Then
    //1) A solution exists if and only if rank(A) = rank(A|N). The solutions form an affine space of dimension = (colums of A - rank(A)).
    //2) If rank(A) < rank(A|N) then there are no solutions.
    //3) rank(A) > rank(A|N) is not possible.
    matrixType fullSystem(theTrainingSet.supports->rows(),
                          theTrainingSet.supports->cols()+1);
    fullSystem << *(theTrainingSet.supports), *(theTrainingSet.values);
    Eigen::FullPivLU<matrixType> luFull(fullSystem);
    double fullRank = luFull.rank();
    Eigen::FullPivLU<matrixType> luSupp(*(theTrainingSet.supports));
    double suppRank = luSupp.rank();
    if (suppRank < fullRank)
        theTrainingSet.overdetermined = true;
    else
        theTrainingSet.overdetermined = false;
    ////////////

    //assert(n < supportRowIndex); //to make sure overdetermined

    return theTrainingSet;
}

rowVectorType_ptr
domainModel::xMDLPAR::xConverter::toSupport(
    domainModel::xMDLPAR::xSupportMask theSupportMask,
    domainModel::xMDLPAR::xContext theContext)
{
    fileIndexType n = theSupportMask.getSize();
    rowVectorType_ptr theSupport(new rowVectorType(n));
    //there might be a better way to do this with a select statement:
    for (fileIndexType i=0; i<n; i++)
    {
        //careful of an off by one -- check out where the supportMask indices come from. they should start at 0.
        fileIndexType theIndex = theSupportMask.theShortenedPositionRanking_ptr->coeff(i);
        theSupport->coeffRef(i) = theContext.codecBuffer_ptr->getByteAsInt(theContext.contextStartIndex+theIndex);
    }

    return theSupport;
}

rowVectorType_ptr
domainModel::xMDLPAR::xConverter::toRawSupportIndices(
    domainModel::xMDLPAR::xSupportMask theSupportMask,
    domainModel::xMDLPAR::xContext theContext)
{
    fileIndexType n = theSupportMask.getSize();
    rowVectorType_ptr theRawSupportIndices(new rowVectorType(n));
    for (fileIndexType i=0; i<n; i++)
    {
        fileIndexType theIndex = theSupportMask.theShortenedPositionRanking_ptr->coeff(i);
        theRawSupportIndices->coeffRef(i) = theContext.contextStartIndex+theIndex;
    }

    return theRawSupportIndices;
}

domainModel::xMDLPAR::xFilterCoefficients
domainModel::xMDLPAR::xConverter::toFilterCoefficients(
    domainModel::xMDLPAR::xTrainingSet theTrainingSet, fileIndexType k)
{
    domainModel::xMDLPAR::xFilterCoefficients theFilterCoefficients;

    assert( theTrainingSet.values->sum() == theTrainingSet.values->sum() );
    assert( theTrainingSet.supports->all() == theTrainingSet.supports->all() ); //!nan?;

    vectorType_ptr filterCoefficientValues(new vectorType(
        theTrainingSet.supports->
            jacobiSvd(Eigen::ComputeThinU|Eigen::ComputeThinV).solve(
                *(theTrainingSet.values))));

    //Eigen::FullPivLU<Eigen::Matrix<double,Eigen::Dynamic,1> > lu(theTrainingSet.supports);
    //Eigen::Matrix<double,k,1> theSupports = *theTrainingSet.supports;
    //Eigen::FullPivLU<matrixType> lu(*(theTrainingSet.supports));
    //theFilterCoefficients.rank = lu.rank();
    //if (theFilterCoefficients.rank >= k) //not overdetermined which we need
    //    return theFilterCoefficients;

    //vectorType_ptr filterCoefficientValues(new vectorType(lu.solve(*(theTrainingSet.values))));

    //vectorType_ptr filterCoefficientValues;
    theFilterCoefficients.filterCoefficients = filterCoefficientValues;

    //assert( filterCoefficientValues->sum() == filterCoefficientValues->sum() ); //!nan?

    //if (filterCoefficientValues->sum() != filterCoefficientValues->sum())
    //{
    //   std::cout << "supports: " << *theTrainingSet.supports << std::endl;
    //    std::cout << "values: " << *theTrainingSet.values << std::endl;
    //    std::cout <<"filtercoeffs: " << *theFilterCoefficients.filterCoefficients << std::endl;
   // }

    assert( filterCoefficientValues->sum() == filterCoefficientValues-> sum() ); //!nan?

    return theFilterCoefficients;
}

//double
//domainModel::xMDLPAR::xConverter::toOneDee(domainModel::xMDLPAR::xContext theContext)
//{
//    symbolsAsValues theValues(toValues(theContext));
//
//    arrayType theDiffs(Eigen::Array<double,Eigen::Dynamic,1>::Zero(G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES-1,1));
//    for (fileIndexType i=0; i<G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES-1; i++)
//        theDiffs(i) = theValues->coeff(i+1)-theValues->coeff(i);
//
//    //mult with the thing here to smear it out
//
//    double theRep = theDiffs.sum();
//    return theRep;
//}
