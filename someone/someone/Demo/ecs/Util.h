#pragma once
#include "Ayy.h"

namespace crude {

class Util
{
public:
    static float GetUnitSize();
    static ayy::Vec3f GetPosAtTile(int row,int col);
    
    // return [low,max]
    static int random(int lowBound,int maxBound);
    
protected:
    static unsigned int random();
};

}

