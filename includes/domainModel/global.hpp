#ifndef DOMAINMODEL_GLOBAL_HPP
#define DOMAINMODEL_GLOBAL_HPP
// define once

#include "boost/smart_ptr/shared_ptr.hpp"
#include "Core" //Eigen/Core
#include <math.h>
#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>

////////////////////////////////////
//big enough to be able to deal with very large files, if necessary
typedef unsigned long fileIndexType;
#define fileIndexTypeSize sizeof(fileIndexType)
///////////////////////////////////

typedef double symbolAsValue;
typedef boost::shared_ptr<Eigen::Map<Eigen::VectorXd> > symbolsAsValues;

//namespace domainModel
//{

    //std::ofstream lg;

    void setup();

    //200 Hz * 2 seconds * ~120 channels * 2 bytes/sample,
    //2 seconds is a little lower than delta waves
    //const fileIndexType G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES = 200*2*120*2;
    const int G_MAGIC_NUMBER_MAX_SYMBOL_VALUE = 255.0;

    //extern const double G_MAGIC_NUMBER_MAX_RAW_CONTEXT_DISTANCE;
    //extern const double G_MAGIC_NUMBER_NORMALIZED_CONTEXT_SIMILARITY_THRESHOLD;
    //extern const double G_MAGIC_NUMBER_NORMALIZED_SUPPORT_SIMILARITY_THRESHOLD;

    const int G_MAGIC_NUMBER_MAX_PREDICTION_ERROR = 255;
    const int G_MAGIC_NUMBER_MIN_PREDICTION_ERROR = -255;
    //alternatively, like 1 second of eeg a la delta, maybe 2 seconds.

    extern unsigned long G_MAGIC_NUMBER_CONTEXT_SIZE_IN_BYTES;
    extern double G_MAGIC_NUMBER_MAX_RAW_CONTEXT_DISTANCE;
    extern double G_MAGIC_NUMBER_NORMALIZED_CONTEXT_SIMILARITY_THRESHOLD;
    extern double G_MAGIC_NUMBER_NORMALIZED_SUPPORT_SIMILARITY_THRESHOLD;
    extern int G_MAGIC_NUMBER_NUM_APPROX_NEIGHBORS_TO_CHECK;
    extern fileIndexType G_MAGIC_NUMBER_MAX_NUM_NEIGHBORS_TO_USE;

    extern std::ofstream lg;
    extern fileIndexType bytesWritten;
    //extern const double G_MAGIC_NUMBER_MAX_RAW_CONTEXT_DISTANCE;

//}

typedef Eigen::Array<double,Eigen::Dynamic,1> arrayType;
typedef boost::shared_ptr<arrayType> arrayType_ptr;

typedef Eigen::Matrix<double,Eigen::Dynamic, 1> vectorType;
typedef boost::shared_ptr<vectorType> vectorType_ptr;

typedef Eigen::Matrix<double,1,Eigen::Dynamic> rowVectorType;
typedef boost::shared_ptr<rowVectorType> rowVectorType_ptr;

typedef Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic> matrixType;
typedef boost::shared_ptr<matrixType> matrixType_ptr;

extern vectorType thePrimes;

//typedef double symbolAsValue;
//typedef arrayType_ptr symbolsAsValues;

#endif

//do this multiple times
//extern const int magicNumberContextSizeInBytes;
