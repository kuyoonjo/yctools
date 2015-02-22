//
//  Random.cpp
//  yctools
//
//  Created by Yu Chen on 2/9/15.
//
//


#include <yctools/Random.h>

int yc::Random::randInt(int min, int max)
{
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    int dice_roll = distribution(generator);
    return dice_roll;
}