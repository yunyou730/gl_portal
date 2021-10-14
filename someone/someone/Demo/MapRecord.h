#pragma once
#include <vector>

namespace crude {

typedef enum
{
    ROAD,
    BLOCK,
    
} ETileType;

class MapRecord
{
public:
    MapRecord();
    ~MapRecord();
    
    void InitDefaultValue();
    
    int GetCols() const { return _cols;}
    int GetRows() const { return _rows;}
    int GetUnitSize() const { return _unitSize; }
    
    ETileType GetTileAt(int row,int col);
    
protected:
    int _cols;
    int _rows;
    int _unitSize = 1;
    
    std::vector<std::vector<ETileType>> _tiles;
};

}
