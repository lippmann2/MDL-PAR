#ifndef DOMAINMODEL_XARITHCODEC_XRANGE_HPP
#define DOMAINMODEL_XARITHCODEC_XRANGE_HPP

#include "domainModel/global.hpp"

namespace domainModel
{
    namespace xArithCodec
    {
        class xRange
        {
            public:
                xRange();
                xRange(int theLow, int theHigh, int theScale);
                int getHighAsInt() const;
                int getLowAsInt() const;
                int getScaleAsInt() const;

            private:
                int highOfRange;
                int lowOfRange;
                int scaleFactor;
        };
    }
}

#endif
