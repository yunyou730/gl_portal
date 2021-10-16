#pragma once
#include "Ayy.h"

namespace crude {

class Util
{
public:
    static float GetUnitSize();
    static ayy::Vec3f GetPosAtTile(int row,int col);
};

}

