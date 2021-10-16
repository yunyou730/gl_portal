#include "MapSingleton.h"

namespace crude
{

MapSingleton::~MapSingleton()
{

}

void MapSingleton::InitDefaultValue()
{
    _tiles.clear();

    _tiles = {
        {
            ETileType(1),ETileType(0),ETileType(1),ETileType(0),ETileType(1),
        },
        {
            ETileType(1),ETileType(0),ETileType(1),ETileType(0),ETileType(1),
        },
        {
            ETileType(1),ETileType(0),ETileType(1),ETileType(0),ETileType(1),
        },
        {
            ETileType(1),ETileType(0),ETileType(1),ETileType(0),ETileType(1),
        },
        {
            ETileType(1),ETileType(0),ETileType(1),ETileType(0),ETileType(1),
        },
        {
            ETileType(1),ETileType(0),ETileType(1),ETileType(0),ETileType(1),
        },
        {
            ETileType(1),ETileType(0),ETileType(1),ETileType(0),ETileType(1),
        },
        {
            ETileType(1),ETileType(0),ETileType(1),ETileType(0),ETileType(1),
        },
        {
            ETileType(1),ETileType(0),ETileType(1),ETileType(0),ETileType(1),
        },
    };

    _rows = (int)_tiles.size();
    _cols = 0;
    for(auto it = _tiles.begin();it != _tiles.end();it++)
    {
        if(it->size() > _cols)
        {
            _cols = (int)it->size();
        }
    }
}


}
