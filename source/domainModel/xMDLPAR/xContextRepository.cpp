#include "domainModel/xMDLPAR/xContextRepository.hpp"

inline bool ccpairdescend(const std::pair<double,domainModel::xMDLPAR::xContext>& lhs,
                   const std::pair<double,domainModel::xMDLPAR::xContext>& rhs)
{
    return lhs.first > rhs.first;
}

domainModel::xMDLPAR::xContextRepository::xContextRepository()
{
    tree = RBTreeCreate(KeyCompare, KeyDestroy, InfoDestroy, KeyPrint, InfoPrint);
}

domainModel::xMDLPAR::xContextRepository::~xContextRepository()
{
    RBTreeDestroy(tree);
}

double*
domainModel::xMDLPAR::xContextRepository::addContext(xContext theContext)
{
    //should always be complete here
    //if (!theContext.isCompleteContext) return;

    xContext* info_ptr = new xContext(theContext);
    double* key_ptr = (double*)malloc(sizeof(double));

    *key_ptr = toOneDee(theContext); //tree will take responsibility

    RBTreeInsert(tree,key_ptr,info_ptr); //want duplicates

    return key_ptr;
}

double
domainModel::xMDLPAR::xContextRepository::toOneDee(domainModel::xMDLPAR::xContext theContext)
{
    //symbolsAsValues theValues(toValues(theContext));

    //assert(theContext.contextStartIndex < 646);

    symbolsAsValues theValues(
        new Eigen::Map<Eigen::VectorXd>(
            &(theContext.codecBuffer_ptr->theByteBuffer[theContext.contextStartIndex]),
                G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES-1,1));

    arrayType theDiffs(Eigen::Array<double,Eigen::Dynamic,1>::Zero(G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES-1,1));
    for (fileIndexType i=0; i<G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES-1; i++)
        theDiffs(i) = theValues->coeff(i+1)-theValues->coeff(i);

    //mult with the thing here to smear it out
    theDiffs = theDiffs.array() * thePrimes.tail(G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES-1).array();

    double theRep = theDiffs.sum();
    return theRep;
}

domainModel::xMDLPAR::xContextList
domainModel::xMDLPAR::xContextRepository::addContextAndGetSimilarContexts(xContext theContext)
{
    domainModel::xMDLPAR::xContextList theContextList;

    if (!theContext.isCompleteContext) return theContextList; //empty

    //std::cout << "si: " << theContext.contextStartIndex << std::endl;

    double* key_ptr = addContext(theContext);
    //rb_red_blk_node* startingNode = RBExactQuery(tree,key_ptr); //may not be exact same one ...
    fileIndexType startingNodeContextStartIndex = theContext.contextStartIndex;
    //... could potentially be smart and traverse to correct one
    rb_red_blk_node* currentNode;

    double theDistance = 0;
    double& theDistanceRef = theDistance;

    //debug
    //domainModel::xMDLPAR::xContext debugStartingContext( *((xContext*)startingNode->info) );
    //std::cout << "dsi: " << theContext.contextStartIndex << std::endl;
    //

    std::vector< std::pair<double, xContext> > candidateContexts;
    candidateContexts.reserve(G_MAGIC_NUMBER_NUM_APPROX_NEIGHBORS_TO_CHECK);

    //look at some predecessors
    currentNode = RBExactQuery(tree,key_ptr);
    for (int i = 0; i<G_MAGIC_NUMBER_NUM_APPROX_NEIGHBORS_TO_CHECK/2; i++)
    {
        currentNode=TreePredecessor(tree,currentNode);
        if(tree->nil == currentNode) break;
        //xContext* bob = ((xContext*)startingNode->info);
        //double bob = ((xContext*)(startingNode->info))->contextStartIndex;
        //if( ((xContext*)(startingNode->info))->contextStartIndex == ((xContext*)currentNode->info)->contextStartIndex) continue; //check we didn't hit real starting node
        if (startingNodeContextStartIndex == ((xContext*)currentNode->info)->contextStartIndex) continue;
        if (theContextsAreSimilarEnough(theContext, *(xContext*)currentNode->info, theDistanceRef))
            candidateContexts.push_back( std::make_pair<double,xContext>(theDistance, xContext(*(xContext*)currentNode->info) ));
            //theContextList.addContext(xContext(*((xContext*)currentNode->info)));

        //assert
        domainModel::xMDLPAR::xContext tempContext( *((xContext*)currentNode->info) );
        assert(tempContext.contextStartIndex + G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES < tempContext.codecBuffer_ptr->theByteBuffer.size());
        //end assert
    }

    //look at some successors
    currentNode = RBExactQuery(tree,key_ptr);
    for (int i = 0; i<G_MAGIC_NUMBER_NUM_APPROX_NEIGHBORS_TO_CHECK/2; i++)
    {
        currentNode=TreeSuccessor(tree,currentNode);
        if(tree->nil == currentNode) break;
        //if( ((xContext*)startingNode->info)->contextStartIndex == ((xContext*)currentNode->info)->contextStartIndex) continue; //check we didn't hit real starting node
        if (startingNodeContextStartIndex == ((xContext*)currentNode->info)->contextStartIndex) continue;
        if (theContextsAreSimilarEnough(theContext, *(xContext*)currentNode->info, theDistanceRef))
            candidateContexts.push_back( std::make_pair<double,xContext>(theDistance, xContext(*(xContext*)currentNode->info) ));
            //theContextList.addContext(xContext(*((xContext*)currentNode->info)));

        //assert
        assert( startingNodeContextStartIndex != ((xContext*)currentNode->info)->contextStartIndex );
        domainModel::xMDLPAR::xContext tempContext2( *((xContext*)currentNode->info) );
        assert(tempContext2.contextStartIndex + G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES < tempContext2.codecBuffer_ptr->theByteBuffer.size());
        //end assert

        //if (theContextList.numContexts() == G_MAGIC_NUMBER_MAX_NUM_NEIGHBORS_TO_USE) break;
    }

    if (candidateContexts.size() == 0) return theContextList;
    //if (candidateContexts.size() == 1)
    //{
    //    theContextList.addContext(candidateContexts[0].second);
    //    return theContextList;
    //}

    //std::sort(candidateContexts.begin(),candidateContexts.end(),ccpairdescend);

    if (candidateContexts.size() < G_MAGIC_NUMBER_MAX_NUM_NEIGHBORS_TO_USE)
    {
        for(fileIndexType i=0; i<candidateContexts.size(); i++)
            theContextList.addContext(candidateContexts[i].second);
    }
    else
    {
        std::sort(candidateContexts.begin(),candidateContexts.end(),ccpairdescend);
        for(fileIndexType i=0; i < G_MAGIC_NUMBER_MAX_NUM_NEIGHBORS_TO_USE; i++)
            theContextList.addContext(candidateContexts[i].second);
    }

    //std::cout << "clls: " << theContextList.numContexts() << std::endl;
    assert(theContextList.numContexts()<= G_MAGIC_NUMBER_MAX_NUM_NEIGHBORS_TO_USE);
    assert(theContextList.numContexts() > 0);

    return theContextList;
}

////theContextsAreSimilarEnough
bool
domainModel::xMDLPAR::xContextRepository::theContextsAreSimilarEnough(
    const domainModel::xMDLPAR::xContext& a,
    const domainModel::xMDLPAR::xContext& b,
    double& theDistance)
{

    if ( !(a.isComplete()) || !(b.isComplete()) )
        return false;

    //is it dealing automatically with the fact that these are pointers?
    //symbolsAsValues aValues = domainModel::xMDLPAR::xConverter::toValues(a);
    //symbolsAsValues bValues = domainModel::xMDLPAR::xConverter::toValues(b);

    symbolsAsValues aValues(
        new Eigen::Map<Eigen::VectorXd>(
            &(a.codecBuffer_ptr->theByteBuffer[a.contextStartIndex]),
                G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES-1,1));

    symbolsAsValues bValues(
        new Eigen::Map<Eigen::VectorXd>(
            &(b.codecBuffer_ptr->theByteBuffer[b.contextStartIndex]),
                G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES-1,1));

    //euclidean distance between the two contexts
    Eigen::VectorXd tempValues;//(G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES);

    tempValues = *aValues - *bValues;
    //double maxDist = G_MAGIC_NUMBER_MAX_RAW_CONTEXT_DISTANCE;

    //QUICK EXPERIMENT::::
    //fileIndexType theSize = G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES;
    //tempValues = (aValues->array() * thePrimes.tail(theSize).array()) -
    //                (bValues->array() * thePrimes.tail(theSize).array());
    //Eigen::VectorXd tempForSum((G_MAGIC_NUMBER_MAX_RAW_CONTEXT_DISTANCE * thePrimes.tail(theSize).array()) *
    //                         (G_MAGIC_NUMBER_MAX_RAW_CONTEXT_DISTANCE * thePrimes.tail(theSize).array()));
    //double maxDist = std::sqrt(tempForSum.sum());
    ///////////////////////

    //std::cout << *aValues << std::endl << std::endl;
    //std::cout << *bValues << std::endl << std::endl;
    //std::cout << tempValues << std::endl << std::endl;

    //tempValues = tempValues.array().square(); //assert or unit test that this actually works

    //std::cout << tempValues << std::endl << std::endl;

    //tempValues = tempValues.square();
    double theRawDistance = tempValues.norm();

    //double theNormalizedSimilarity = 1- (theRawDistance/maxDist);
    double theNormalizedSimilarity = 1 - (theRawDistance/G_MAGIC_NUMBER_MAX_RAW_CONTEXT_DISTANCE);
    bool similarEnough;
    if (theNormalizedSimilarity >=
            G_MAGIC_NUMBER_NORMALIZED_CONTEXT_SIMILARITY_THRESHOLD)
                similarEnough = true;
            else
                similarEnough = false;

    theDistance = theNormalizedSimilarity;

    //if (similarEnough)
    //    std::cout << "se: " << theNormalizedSimilarity << std::endl;

    return similarEnough;
}
////

/////////////
    //int
    //domainModel::xMDLPAR::xContextRepository::
    int
    KeyCompare(const void* a, const void* b)
    {
        if( *(double*)a > *(double*)b) return(1);
        if( *(double*)b > *(double*)b) return(-1);
        return(0);
    }

    //oid
    //domainModel::xMDLPAR::xContextRepository::
    void
    KeyDestroy(void* a)
    {
        free((double*)a);
    }

    //void
    //domainModel::xMDLPAR::xContextRepository::
    void
    InfoDestroy(void* a)
    {
        delete((domainModel::xMDLPAR::xContext*)a);
    }

    //void domainModel::xMDLPAR::xContextRepository::
    void KeyPrint(const void* a){;}
    //void domainModel::xMDLPAR::xContextRepository::
    void InfoPrint(void* a){;}
