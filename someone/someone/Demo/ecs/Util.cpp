#include "Util.h"

namespace crude
{

float Util::GetUnitSize()
{
    return 0.2;
}

ayy::Vec3f Util::GetPosAtTile(int row,int col)
{
    float x = col * GetUnitSize();
    float y = 0;
    float z = row * GetUnitSize();
    return ayy::Vec3f(x,y,z);
}

}

