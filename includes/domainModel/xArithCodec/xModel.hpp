#ifndef DOMAINMODEL_XARITHCODEC_XMODEL_HPP
#define DOMAINMODEL_XARITHCODEC_XMODEL_HPP

#include "domainModel/global.hpp"

#include "domainModel/xArithCodec/xRange.hpp"

namespace domainModel
{
    namespace xArithCodec
    {
        class xModel
        {
        public:
            xModel() {};
            ~xModel() {};
            virtual int GetSymbolValue(int thePositionRangeValue) = 0;
            virtual domainModel::xArithCodec::xRange GetRange(int theSymbolValue) = 0;
            virtual short int getScale() = 0;
        private:

            ////
            //static const int magicNumberMinByteIndex = 0;
            //static const int magicNumberMaxByteIndex = 255;
            //static const int magicNumberNumStatesOfAByte = 256;

            ////

            //xModel& operator=(const xModel&); xModel isn't actually an interface, so i am allowing generated copy functions
        };
    }
}

#endif
