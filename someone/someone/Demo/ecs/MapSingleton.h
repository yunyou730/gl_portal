#pragma once
#include "Ayy.h"
#include "Define.h"
#include "SingletonComponent.h"
#include <vector>

namespace crude {
class MapSingleton : public SingletonComponent
{
public:
    virtual ~MapSingleton();
    
    void InitDefaultValue();
    
    int GetCols() const { return _cols;}
    int GetRows() const { return _rows;}
    
    ETileType GetTileAt(int row,int col);
    ayy::Vec2i GetSize() const
    {
        return ayy::Vec2i(_rows,_cols);
    }
    
public:
    int _cols;
    int _rows;
    std::vector<std::vector<ETileType>> _tiles;
};

}

