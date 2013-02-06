#include "domainModel/xArithCodec/xRange.hpp"

domainModel::xArithCodec::xRange::xRange() {}

domainModel::xArithCodec::xRange::xRange(int theLow, int theHigh, int theScale)
{
    highOfRange = theHigh;
    lowOfRange = theLow;
    scaleFactor = theScale;
}

int domainModel::xArithCodec::xRange::getHighAsInt() const {return highOfRange;}
int domainModel::xArithCodec::xRange::getLowAsInt() const {return lowOfRange;}
int domainModel::xArithCodec::xRange::getScaleAsInt() const {return scaleFactor;}
