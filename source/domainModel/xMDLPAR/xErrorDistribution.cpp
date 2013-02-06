#include "domainModel/xMDLPAR/xErrorDistribution.hpp"
#include <cmath>

domainModel::xMDLPAR::xErrorDistribution::xErrorDistribution(double theStd)
{
    theStandardDeviation = theStd; //(theStd + 1) * 1.5; //theStd //oh man...
    if (theStandardDeviation == 0)
        flatDistribution = true;
}

const double domainModel::xMDLPAR::xErrorDistribution::flatDistributionHeight =
    1.0/(G_MAGIC_NUMBER_MAX_PREDICTION_ERROR - G_MAGIC_NUMBER_MIN_PREDICTION_ERROR + 1); //256=number of byte states
const double domainModel::xMDLPAR::xErrorDistribution::maxAbsoluteError = G_MAGIC_NUMBER_MAX_PREDICTION_ERROR; //e.g. 0-255

domainModel::xMDLPAR::xErrorDistribution::xErrorDistribution() {}

double domainModel::xMDLPAR::xErrorDistribution::Pd(int theSymbolError)
{

    using namespace std;

    double y, A, B;

    const double s = theStandardDeviation;
    const int d = theSymbolError;

    //if (flatDistribution)
    //{
    //    return flatDistributionHeight;
    //}

    if (theSymbolError == 0)
    {
        y = 1 - exp( -1/( M_SQRT2 * s ) );
    }
    else if ( ( 0 < abs(d) ) && ( abs(d) < maxAbsoluteError ) )
    {
        A = exp( -( abs(d)-0.5 )/( s/M_SQRT2 ) );
        B = exp( -( abs(d)+0.5 )/( s/M_SQRT2 ) );
        y = 0.5 * ( A - B );
    }
    else if ( abs(d) == maxAbsoluteError )
        y = 0.5 * exp( -( abs(d)-0.5 )/( s/M_SQRT2 ) );

    return y;

}

bool domainModel::xMDLPAR::xErrorDistribution::isFlat()
{
    return flatDistribution;
}
