//
//  Random.h
//  yctools
//
//  Created by Yu Chen on 2/9/15.
//
//

#ifndef yctools_Random_h
#define yctools_Random_h

#include <stdlib.h>
#include <ctime>
#include <random>

#include "Export.h"
namespace yc
{
    class YCTOOLS_API Random
    {
    public:
        int randInt(int min, int max);
        float randFloat(float min, float max);
    };
}

#endif
