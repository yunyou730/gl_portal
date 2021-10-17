#include "Util.h"

namespace crude
{

static unsigned int RANDOM_SEED = 417;
const static unsigned int RAND_CLAMPER = 65536;

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

int Util::random(int lowBound,int maxBound)
{
    unsigned int value = random();
    float pct = float(value) / float(RAND_CLAMPER);
    return lowBound + int((maxBound - lowBound) * pct);
}

unsigned int Util::random()
{
    RANDOM_SEED = (RANDOM_SEED * 123 + 59) % 65536;   // [0,65535]
    return RANDOM_SEED;
}


}

