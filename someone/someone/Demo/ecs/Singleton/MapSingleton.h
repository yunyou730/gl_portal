#pragma once
#include "Ayy.h"
#include "Define.h"
#include "SingletonComponent.h"
#include <vector>

namespace crude {

struct PresetRecord;
class MapSingleton : public SingletonComponent
{
public:
    virtual ~MapSingleton();
    
    void InitDefaultValue();
    
    int GetCols() const { return _cols;}
    int GetRows() const { return _rows;}
    
    ayy::Vec2i GetSize() const
    {
        return ayy::Vec2i(_rows,_cols);
    }
    
    void AddPreset(EActorType actorType,int row,int col);
    
    
    void ClearPreset();

    
public:
    int _cols;
    int _rows;
    std::vector<PresetRecord*>  _presetRecords;
};

struct PresetRecord
{
    PresetRecord(EActorType actorType,int row,int col)
        :actorType(actorType),row(row),col(col)
    {}
    
    EActorType actorType = EActorType::AT_None;
    int row = 0;
    int col = 0;
};

}

