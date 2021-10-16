#include "MapSingleton.h"

namespace crude
{

MapSingleton::~MapSingleton()
{

}

void MapSingleton::InitDefaultValue()
{
    _rows = 60;
    _cols = 55;
    
//    _rows = 1000;
//    _cols = 1000;
}

ETileType MapSingleton::GetTileAt(int row,int col)
{
    return ETileType::Road;
}


}
